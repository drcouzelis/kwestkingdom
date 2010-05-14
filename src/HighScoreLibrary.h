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
#ifndef __HIGH_SCORE_LIBRARY_H
#define __HIGH_SCORE_LIBRARY_H


#define MAX_NUM_OF_HIGH_SCORES 5


typedef struct {
  char initials[4];
  int room;
  int coins;
} HighScore;


void init_high_scores();

int high_score_position(int room, int coins);

void add_high_score(char* initials, int room, int coins);

bool get_high_score(int num, char* retInitials, int* retRoom, int* retCoins);


#endif // __HIGH_SCORE_LIBRARY_H
