#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "HighScoreLibrary.h"


static char highScoresFilename[FILENAME_MAX];

static HighScoreLibrary *highScoreLibraryInstance = NULL;
static HighScore highScores[MAX_NUM_OF_HIGH_SCORES];
static int numOfHighScores;


void writeHighScores() {
  
  FILE *file;
  int i;
  
  file = fopen(highScoresFilename, "w");
  
  if (file == NULL) {
    return;
  }
  
  for (i = 0; i < numOfHighScores; i++) {
    fprintf(file, "%s %d %d\n", highScores[i].initials, highScores[i].room, highScores[i].coins);
  }
  
  fclose(file);
  
}


void readHighScores() {
  
  FILE *file;
  char line[256];
  
  numOfHighScores = 0;
  
  file = fopen(highScoresFilename, "r");
  
  if (file == NULL) {
    return;
  }
  
  while (fgets(line, 255, file) != NULL) {
    sscanf(line, "%s %d %d", highScores[numOfHighScores].initials, &(highScores[numOfHighScores].room),&(highScores[numOfHighScores].coins));
    numOfHighScores++;
  }
  
  fclose(file);
  
}





void HighScoreLibrary::initInstance() {

  char *path;
  int i;

  if (highScoreLibraryInstance == NULL) {

    // Load the high score filename
    path = getenv("XDG_CONFIG_HOME");
    if (path && path[0] != '\0') {
      strcpy(highScoresFilename, path);
    } else {
      // If XDG variables aren't set, then just use the home directory
      strcpy(highScoresFilename, getenv("HOME"));
      strcat(highScoresFilename, "/.config");
    }
    strcat(highScoresFilename, "/kwestkingdom");
    // Create the config file directory, in case it doesn't exist
    mkdir(highScoresFilename, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    strcat(highScoresFilename, "/highscores.txt");

    highScoreLibraryInstance = new HighScoreLibrary();
    for (i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
      strcpy(highScores[i].initials, "\0");
      highScores[i].room = 0;
      highScores[i].coins = 0;
    }
    numOfHighScores = 0;
    readHighScores();
  }
}


void HighScoreLibrary::deallocInstance() {
  delete highScoreLibraryInstance;
}


HighScoreLibrary::HighScoreLibrary() {
}


HighScoreLibrary::~HighScoreLibrary() {
}


int HighScoreLibrary::highScorePosition(int room, int coins) {
  
  int position;
  int i;
  
  position = numOfHighScores;
  
  for (i = numOfHighScores - 1; i >= 0; i--) {
    if (room > highScores[i].room) {
      position = i;
    } else if (room == highScores[i].room) {
      if (coins > highScores[i].coins) {
        position = i;
      } else if (coins == highScores[i].coins) {
        position = i + 1;
      }
    }
  }
  
  return position;
  
}


void HighScoreLibrary::addHighScore(char *initials, int room, int coins) {
  
  int position;
  int i;
  
  position = HighScoreLibrary::highScorePosition(room, coins);
  
  if (position == MAX_NUM_OF_HIGH_SCORES) {
    return;
  }
  
  for (i = MAX_NUM_OF_HIGH_SCORES - 2; i >= position; i--) {
    strcpy(highScores[i + 1].initials, highScores[i].initials);
    highScores[i + 1].room = highScores[i].room;
    highScores[i + 1].coins = highScores[i].coins;
  }
  
  strcpy(highScores[position].initials, initials);
  highScores[position].room = room;
  highScores[position].coins = coins;
  
  numOfHighScores++;
  
  writeHighScores();
  readHighScores();
  
}


bool HighScoreLibrary::getHighScore(int num, char *initials, int *room, int * coins) {
  if (num < numOfHighScores) {
    strcpy(initials, highScores[num].initials);
    *room = highScores[num].room;
    *coins = highScores[num].coins;
    return true;
  }
  return false;
}



