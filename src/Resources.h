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
#ifndef __RESOURCES_H
#define __RESOURCES_H


#include <allegro.h>


typedef enum {
  IMG_SWORD_STAB_2,
  IMG_SWORD_STAB_4,
  IMG_SWORD_STAB_3,
  IMG_SWORD_STAB_1,
  IMG_SWORD_HOLD_2,
  IMG_SWORD_HOLD_4,
  IMG_SWORD_HOLD_3,
  IMG_SWORD_HOLD_1,
  IMG_SHIELD_2,
  IMG_SHIELD_4,
  IMG_SHIELD_3,
  IMG_SHIELD_1,
  IMG_TITLE,
  IMG_CHOMPER_BITE_2,
  IMG_CHOMPER_BITE_4,
  IMG_CHOMPER_BITE_5,
  IMG_CHOMPER_BITE_3,
  IMG_CHOMPER_BITE_1,
  IMG_CHOMPER_STAND_2,
  IMG_CHOMPER_STAND_3,
  IMG_CHOMPER_STAND_1,
  IMG_HERO_HURT_2,
  IMG_HERO_HURT_4,
  IMG_HERO_HURT_3,
  IMG_HERO_HURT_1,
  IMG_HERO_DIE_2,
  IMG_HERO_DIE_4,
  IMG_HERO_DIE_5,
  IMG_HERO_DIE_3,
  IMG_HERO_DIE_1,
  IMG_HERO_ATTACK_2,
  IMG_HERO_ATTACK_4,
  IMG_HERO_ATTACK_3,
  IMG_HERO_ATTACK_1,
  IMG_HERO_STAND_2,
  IMG_HERO_STAND_3,
  IMG_HERO_STAND_1,
  IMG_ARCHER_2,
  IMG_ARCHER_3,
  IMG_ARCHER_1,
  IMG_ITEMS_EMPTYHEART,
  IMG_ITEMS_HEART,
  IMG_ITEMS_MONEYBAG,
  IMG_TERRAIN_DOWNSTAIRS,
  IMG_TERRAIN_WATER,
  IMG_TERRAIN_DIRT,
  IMG_TERRAIN_ICE,
  IMG_TERRAIN_PATH,
  IMG_TERRAIN_SPIRE,
  IMG_TERRAIN_OAK,
  IMG_TERRAIN_UPSTAIRS,
  IMG_TERRAIN_SNOW,
  IMG_TERRAIN_EVERGREEN,
  IMG_TERRAIN_GRASS,
  IMG_HAMMER_SWING_2,
  IMG_HAMMER_SWING_4,
  IMG_HAMMER_SWING_3,
  IMG_HAMMER_SWING_1,
  IMG_HAMMER_HOLD_2,
  IMG_HAMMER_HOLD_4,
  IMG_HAMMER_HOLD_3,
  IMG_HAMMER_HOLD_1,
  IMG_BOW_DRAW_2,
  IMG_BOW_DRAW_3,
  IMG_BOW_DRAW_1,
  IMG_BOW_HOLD_2,
  IMG_BOW_HOLD_4,
  IMG_BOW_HOLD_3,
  IMG_BOW_HOLD_1,
  IMG_GIANT_2,
  IMG_GIANT_3,
  IMG_GIANT_1,
  IMG_ARROW,
  IMG_SHORE_SNOW_INSIDECORNER,
  IMG_SHORE_SNOW_OUTSIDECORNER,
  IMG_SHORE_SNOW_SHORE,
  IMG_SHORE_GRASS_INSIDECORNER,
  IMG_SHORE_GRASS_OUTSIDECORNER,
  IMG_SHORE_GRASS_SHORE,
  IMG_HELP,
  IMG_GAMEOVER,
  IMG_PALETTE,
  IMG_NINJA_2,
  IMG_NINJA_3,
  IMG_NINJA_1,
  NUMBER_OF_IMAGES
} IMAGES;


typedef enum {
  SND_MONEY,
  SND_ARROW_HIT,
  SND_ARROW_FLY,
  SND_HEART,
  SND_GASP,
  SND_SWORD,
  SND_HAMMER,
  SND_CHOMP,
  NUMBER_OF_SOUNDS
} SOUNDS;


void init_resources();
void free_resources();

BITMAP* get_image(int image);
void    set_palette(void);

void play_sound(int sound);
void toggle_sound(void);

bool sound_enabled(void);


#endif // __RESOURCES_H
