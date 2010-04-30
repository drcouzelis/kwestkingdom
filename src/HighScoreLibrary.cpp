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
#import "HighScoreLibrary.h"


#define HIGH_SCORES_FILENAME "highscores.txt"


static HighScoreLibrary *highScoreLibraryInstance = NULL;
static HighScore highScores[MAX_NUM_OF_HIGH_SCORES];
static int numOfHighScores;


void writeHighScores() {
  
  FILE *file;
  int i;
  
  file = fopen(HIGH_SCORES_FILENAME, "w");
  
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


@implementation HighScoreLibrary


+ initInstance {
  int i;
  if (highScoreLibraryInstance == NULL) {
    highScoreLibraryInstance = [[HighScoreLibrary alloc] init];
    for (i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
      strcpy(highScores[i].initials, "\0");
      highScores[i].room = 0;
      highScores[i].coins = 0;
    }
    numOfHighScores = 0;
    readHighScores();
  }
  return highScoreLibraryInstance;
}


+ freeInstance {
  highScoreLibraryInstance = [highScoreLibraryInstance free];
  return highScoreLibraryInstance;
}


+ (int) highScorePositionWithRoom: (int) room andCoins: (int) coins {
  
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


+ addHighScoreWithInitials: (char *) initials andRoom: (int) room andCoins: (int) coins {
  
  int position;
  int i;
  
  position = [HighScoreLibrary highScorePositionWithRoom: room andCoins: coins];
  
  if (position == MAX_NUM_OF_HIGH_SCORES) {
    return self;
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
  
  return self;
  
}


+ (BOOL) getHighScoreNumber: (int) num returnInitials: (char *) initials andRoom: (int *) room andCoins: (int *) coins {
  if (num < numOfHighScores) {
    strcpy(initials, highScores[num].initials);
    *room = highScores[num].room;
    *coins = highScores[num].coins;
    return YES;
  }
  return NO;
}


@end
