/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
#include <cstdio>
#include <cstring>

#include "HighScoreLibrary.h"


#define HIGH_SCORES_FILENAME "highscores.txt"


static HighScore highScores[MAX_NUM_OF_HIGH_SCORES];
static int numOfHighScores;


void write_high_scores()
{
  FILE* file = fopen(HIGH_SCORES_FILENAME, "w");
  
  if (file == NULL) {
    return;
  }
  
  for (int i = 0; i < numOfHighScores; i++) {
    fprintf(file, "%s %d %d\n", highScores[i].initials, highScores[i].room, highScores[i].coins);
  }
  
  fclose(file);
  
}


void read_high_scores()
{
  FILE* file;
  char line[256];
  
  numOfHighScores = 0;
  
  file = fopen(HIGH_SCORES_FILENAME, "r");
  
  if (file == NULL) {
    return;
  }
  
  while (fgets(line, 255, file) != NULL) {
    sscanf(line, "%s %d %d", highScores[numOfHighScores].initials, &(highScores[numOfHighScores].room), &(highScores[numOfHighScores].coins));
    numOfHighScores++;
  }
  
  fclose(file);
  
}


void init_high_scores()
{
  for (int i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
    strcpy(highScores[i].initials, "\0");
    highScores[i].room = 0;
    highScores[i].coins = 0;
  }
  numOfHighScores = 0;
  read_high_scores();
}


int high_score_position(int room, int coins)
{
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


void add_high_score(char* initials, int room, int coins)
{
  int position;
  int i;
  
  position = high_score_position(room, coins);
  
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
  
  write_high_scores();
  read_high_scores();
}


bool get_high_score(int num, char* initials, int* room, int* coins)
{
  if (num < numOfHighScores) {
    strcpy(initials, highScores[num].initials);
    *room = highScores[num].room;
    *coins = highScores[num].coins;
    return true;
  }
  return false;
}

