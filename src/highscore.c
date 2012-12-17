#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "highscore.h"


/* Whether or not the high scores have been initialized */
static int high_scores_initialized = 0;

/* Path and filename to the saved high scores file */
static char high_scores_filename[FILENAME_MAX];

/* A list of the current high scores */
static HIGH_SCORE high_scores[MAX_NUM_OF_HIGH_SCORES];
static int num_high_scores = 0;


void write_high_scores()
{
  FILE *file;
  int i;
  
  file = fopen(high_scores_filename, "w");
  
  if (file == NULL) {
    return;
  }
  
  for (i = 0; i < num_high_scores; i++) {
    fprintf(file, "%s %d %d\n", high_scores[i].initials, high_scores[i].room, high_scores[i].money);
  }
  
  fclose(file);
}


void read_high_scores()
{
  FILE *file;
  char line[256];
  
  file = fopen(high_scores_filename, "r");
  
  if (file == NULL) {
    return;
  }
  
  /* Clear the high score list */
  for (i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
    strcpy(high_scores[i].initials, "\0");
    high_scores[i].room = 0;
    high_scores[i].money = 0;
  }

  num_high_scores = 0;

  while (num_high_scores < MAX_NUM_OF_HIGH_SCORES && fgets(line, 255, file) != NULL) {
    sscanf(line, "%s %d %d", high_scores[num_high_scores].initials, &(high_scores[num_high_scores].room),&(high_scores[num_high_scores].money));
    num_high_scores++;
  }
  
  fclose(file);
}


void initialize_high_scores()
{
  char *path;
  int i;

  if (high_scores_initialized) {
    return;
  }

  /* Load the high score filename */
  path = getenv("XDG_CONFIG_HOME");
  if (path && path[0] != '\0') {
    strcpy(high_scores_filename, path);
  } else {
    /* If XDG variables aren't set, then just use the home directory */
    strcpy(high_scores_filename, getenv("HOME"));
    strcat(high_scores_filename, "/.config");
  }
  strcat(high_scores_filename, "/kwestkingdom");
  /* Create the config file directory, in case it doesn't exist */
  mkdir(high_scores_filename, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
  strcat(high_scores_filename, "/highscores.txt");

  read_high_scores();
}


int high_score_pos(int room, int money)
{
  int pos;
  int i;
  
  initialize_high_scores()

  pos = num_high_scores;
  
  /* Go backwards through the high scores until you find where it goes */
  for (i = num_high_scores - 1; i >= 0; i--) {
    if (room > high_scores[i].room) {
      pos = i;
    } else if (room == high_scores[i].room) {
      if (money > high_scores[i].money) {
        pos = i;
      } else if (money == high_scores[i].money) {
        pos = i + 1;
      }
    }
  }
  
  return pos;
}


void add_high_score(char *initials, int room, int money)
{
  int pos;
  int i;
  
  initialize_high_scores()

  /* Decide if this is a high score */
  pos = high_score_pos(room, money);
  if (pos == MAX_NUM_OF_HIGH_SCORES) {
    return;
  }
  
  /* Shift the high scores to make room for the new one */
  if (pos < num_high_scores) {
    for (i = MAX_NUM_OF_HIGH_SCORES - 2; i >= pos; i--) {
      strcpy(high_scores[i + 1].initials, high_scores[i].initials);
      high_scores[i + 1].room = high_scores[i].room;
      high_scores[i + 1].money = high_scores[i].money;
    }
  }
  
  /* Add the new high score */
  strcpy(high_scores[pos].initials, initials);
  high_scores[pos].room = room;
  high_scores[pos].money = money;

  /* Increment the number of high scores if necessary */  
  if (num_high_scores < MAX_NUM_OF_HIGH_SCORES - 1) {
    num_high_scores++;
  }
  
  write_high_scores();
}


int get_high_score(int pos, HIGH_SCORE *high_score)
{
  if (num < num_high_scores) {
    strcpy(high_score->initials, high_scores[num].initials);
    high_score->room = high_scores[num].room;
    high_score->money = high_scores[num].money;
    return 1;
  }

  /* High score not found, return false */
  return 0;
}

