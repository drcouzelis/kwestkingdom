#include <stdio.h>
#include "colors.h"
#include "resources.h"




/**
 * Private
 */




/**
 * A list of all the images used in the game.
 * This speeds up the game by only loading each image once.
 * The "formats" are the different ways an image can be
 * rotated and flipped.
 */
static BITMAP *images[NUM_IMAGES][NUM_IMAGE_FORMATS];

static SAMPLE *sounds[NUM_SOUNDS];

static PALETTE palette;

static FLAG resources_initialized = OFF;




void load_formatted_image(int image, int format)
{
  BITMAP *orig = images[image][NORMAL];
  BITMAP *temp;
  
  images[image][format] = create_bitmap(orig->w, orig->h);
  clear_to_color(images[image][format], MAGICPINK);
  
  /**
   * For some silly reason, Allegro won't rotate a sprite properly
   * unless I blit it to a temporary bitmap first.
   */
  temp = create_bitmap(orig->w, orig->h);
  blit(orig, temp, 0, 0, 0, 0, temp->w, temp->h);
  
  switch (format) {
  
  case H_FLIP:
    draw_sprite_h_flip(images[image][format], temp, 0, 0);
    break;
    
  case V_FLIP:
    draw_sprite_v_flip(images[image][format], temp, 0, 0);
    break;
    
  case H_V_FLIP:
    rotate_sprite(images[image][format], temp, 0, 0, itofix(128));
    break;
    
  case ROTATE:
    rotate_sprite(images[image][format], temp, 0, 0, itofix(64));
    break;
    
  case ROTATE_H_FLIP:
    rotate_sprite_v_flip(images[image][format], temp, 0, 0, itofix(192));
    break;
    
  case ROTATE_V_FLIP:
    rotate_sprite_v_flip(images[image][format], temp, 0, 0, itofix(64));
    break;
    
  case ROTATE_H_V_FLIP:
    rotate_sprite(images[image][format], temp, 0, 0, itofix(192));
    break;
  }
  
  destroy_bitmap(temp);
}




/**
 * Public
 */




FLAG init_resources()
{
  int i;
  int j;

  if (resources_initialized) {
    return ON;
  }

  for (i = 0; i < NUM_IMAGES; i++) {
    for (j = 0; j < NUM_IMAGE_FORMATS; j++) {
      images[i][j] = NULL;
    }
  }
  
  images[IMG_SWORD_STAB_2][NORMAL] = load_bitmap("img/sword/stab/2.bmp", palette);
  images[IMG_SWORD_STAB_4][NORMAL] = load_bitmap("img/sword/stab/4.bmp", palette);
  images[IMG_SWORD_STAB_3][NORMAL] = load_bitmap("img/sword/stab/3.bmp", palette);
  images[IMG_SWORD_STAB_1][NORMAL] = load_bitmap("img/sword/stab/1.bmp", palette);
  images[IMG_SWORD_HOLD_2][NORMAL] = load_bitmap("img/sword/hold/2.bmp", palette);
  images[IMG_SWORD_HOLD_4][NORMAL] = load_bitmap("img/sword/hold/4.bmp", palette);
  images[IMG_SWORD_HOLD_3][NORMAL] = load_bitmap("img/sword/hold/3.bmp", palette);
  images[IMG_SWORD_HOLD_1][NORMAL] = load_bitmap("img/sword/hold/1.bmp", palette);
  images[IMG_SHIELD_2][NORMAL] = load_bitmap("img/shield/2.bmp", palette);
  images[IMG_SHIELD_4][NORMAL] = load_bitmap("img/shield/4.bmp", palette);
  images[IMG_SHIELD_3][NORMAL] = load_bitmap("img/shield/3.bmp", palette);
  images[IMG_SHIELD_1][NORMAL] = load_bitmap("img/shield/1.bmp", palette);
  images[IMG_TITLE][NORMAL] = load_bitmap("img/title.bmp", palette);
  images[IMG_CHOMPER_BITE_2][NORMAL] = load_bitmap("img/chomper/bite/2.bmp", palette);
  images[IMG_CHOMPER_BITE_4][NORMAL] = load_bitmap("img/chomper/bite/4.bmp", palette);
  images[IMG_CHOMPER_BITE_5][NORMAL] = load_bitmap("img/chomper/bite/5.bmp", palette);
  images[IMG_CHOMPER_BITE_3][NORMAL] = load_bitmap("img/chomper/bite/3.bmp", palette);
  images[IMG_CHOMPER_BITE_1][NORMAL] = load_bitmap("img/chomper/bite/1.bmp", palette);
  images[IMG_CHOMPER_STAND_2][NORMAL] = load_bitmap("img/chomper/stand/2.bmp", palette);
  images[IMG_CHOMPER_STAND_3][NORMAL] = load_bitmap("img/chomper/stand/3.bmp", palette);
  images[IMG_CHOMPER_STAND_1][NORMAL] = load_bitmap("img/chomper/stand/1.bmp", palette);
  images[IMG_HERO_HURT_2][NORMAL] = load_bitmap("img/hero/hurt/2.bmp", palette);
  images[IMG_HERO_HURT_4][NORMAL] = load_bitmap("img/hero/hurt/4.bmp", palette);
  images[IMG_HERO_HURT_3][NORMAL] = load_bitmap("img/hero/hurt/3.bmp", palette);
  images[IMG_HERO_HURT_1][NORMAL] = load_bitmap("img/hero/hurt/1.bmp", palette);
  images[IMG_HERO_DIE_2][NORMAL] = load_bitmap("img/hero/die/2.bmp", palette);
  images[IMG_HERO_DIE_4][NORMAL] = load_bitmap("img/hero/die/4.bmp", palette);
  images[IMG_HERO_DIE_5][NORMAL] = load_bitmap("img/hero/die/5.bmp", palette);
  images[IMG_HERO_DIE_3][NORMAL] = load_bitmap("img/hero/die/3.bmp", palette);
  images[IMG_HERO_DIE_1][NORMAL] = load_bitmap("img/hero/die/1.bmp", palette);
  images[IMG_HERO_ATTACK_2][NORMAL] = load_bitmap("img/hero/attack/2.bmp", palette);
  images[IMG_HERO_ATTACK_4][NORMAL] = load_bitmap("img/hero/attack/4.bmp", palette);
  images[IMG_HERO_ATTACK_3][NORMAL] = load_bitmap("img/hero/attack/3.bmp", palette);
  images[IMG_HERO_ATTACK_1][NORMAL] = load_bitmap("img/hero/attack/1.bmp", palette);
  images[IMG_HERO_STAND_2][NORMAL] = load_bitmap("img/hero/stand/2.bmp", palette);
  images[IMG_HERO_STAND_3][NORMAL] = load_bitmap("img/hero/stand/3.bmp", palette);
  images[IMG_HERO_STAND_1][NORMAL] = load_bitmap("img/hero/stand/1.bmp", palette);
  images[IMG_ARCHER_2][NORMAL] = load_bitmap("img/archer/2.bmp", palette);
  images[IMG_ARCHER_3][NORMAL] = load_bitmap("img/archer/3.bmp", palette);
  images[IMG_ARCHER_1][NORMAL] = load_bitmap("img/archer/1.bmp", palette);
  images[IMG_ITEMS_EMPTYHEART][NORMAL] = load_bitmap("img/items/emptyheart.bmp", palette);
  images[IMG_ITEMS_HEART][NORMAL] = load_bitmap("img/items/heart.bmp", palette);
  images[IMG_ITEMS_MONEYBAG][NORMAL] = load_bitmap("img/items/moneybag.bmp", palette);
  images[IMG_TERRAIN_DOWNSTAIRS][NORMAL] = load_bitmap("img/terrain/downstairs.bmp", palette);
  images[IMG_TERRAIN_WATER][NORMAL] = load_bitmap("img/terrain/water.bmp", palette);
  images[IMG_TERRAIN_DIRT][NORMAL] = load_bitmap("img/terrain/dirt.bmp", palette);
  images[IMG_TERRAIN_ICE][NORMAL] = load_bitmap("img/terrain/ice.bmp", palette);
  images[IMG_TERRAIN_PATH][NORMAL] = load_bitmap("img/terrain/path.bmp", palette);
  images[IMG_TERRAIN_SPIRE][NORMAL] = load_bitmap("img/terrain/spire.bmp", palette);
  images[IMG_TERRAIN_OAK][NORMAL] = load_bitmap("img/terrain/oak.bmp", palette);
  images[IMG_TERRAIN_UPSTAIRS][NORMAL] = load_bitmap("img/terrain/upstairs.bmp", palette);
  images[IMG_TERRAIN_SNOW][NORMAL] = load_bitmap("img/terrain/snow.bmp", palette);
  images[IMG_TERRAIN_EVERGREEN][NORMAL] = load_bitmap("img/terrain/evergreen.bmp", palette);
  images[IMG_TERRAIN_GRASS][NORMAL] = load_bitmap("img/terrain/grass.bmp", palette);
  images[IMG_HAMMER_SWING_2][NORMAL] = load_bitmap("img/hammer/swing/2.bmp", palette);
  images[IMG_HAMMER_SWING_4][NORMAL] = load_bitmap("img/hammer/swing/4.bmp", palette);
  images[IMG_HAMMER_SWING_3][NORMAL] = load_bitmap("img/hammer/swing/3.bmp", palette);
  images[IMG_HAMMER_SWING_1][NORMAL] = load_bitmap("img/hammer/swing/1.bmp", palette);
  images[IMG_HAMMER_HOLD_2][NORMAL] = load_bitmap("img/hammer/hold/2.bmp", palette);
  images[IMG_HAMMER_HOLD_4][NORMAL] = load_bitmap("img/hammer/hold/4.bmp", palette);
  images[IMG_HAMMER_HOLD_3][NORMAL] = load_bitmap("img/hammer/hold/3.bmp", palette);
  images[IMG_HAMMER_HOLD_1][NORMAL] = load_bitmap("img/hammer/hold/1.bmp", palette);
  images[IMG_BOW_DRAW_2][NORMAL] = load_bitmap("img/bow/draw/2.bmp", palette);
  images[IMG_BOW_DRAW_3][NORMAL] = load_bitmap("img/bow/draw/3.bmp", palette);
  images[IMG_BOW_DRAW_1][NORMAL] = load_bitmap("img/bow/draw/1.bmp", palette);
  images[IMG_BOW_HOLD_2][NORMAL] = load_bitmap("img/bow/hold/2.bmp", palette);
  images[IMG_BOW_HOLD_4][NORMAL] = load_bitmap("img/bow/hold/4.bmp", palette);
  images[IMG_BOW_HOLD_3][NORMAL] = load_bitmap("img/bow/hold/3.bmp", palette);
  images[IMG_BOW_HOLD_1][NORMAL] = load_bitmap("img/bow/hold/1.bmp", palette);
  images[IMG_GIANT_2][NORMAL] = load_bitmap("img/giant/2.bmp", palette);
  images[IMG_GIANT_3][NORMAL] = load_bitmap("img/giant/3.bmp", palette);
  images[IMG_GIANT_1][NORMAL] = load_bitmap("img/giant/1.bmp", palette);
  images[IMG_ARROW][NORMAL] = load_bitmap("img/arrow.bmp", palette);
  images[IMG_SHORE_SNOW_INSIDECORNER][NORMAL] = load_bitmap("img/shore/snow/insidecorner.bmp", palette);
  images[IMG_SHORE_SNOW_OUTSIDECORNER][NORMAL] = load_bitmap("img/shore/snow/outsidecorner.bmp", palette);
  images[IMG_SHORE_SNOW_SHORE][NORMAL] = load_bitmap("img/shore/snow/shore.bmp", palette);
  images[IMG_SHORE_GRASS_INSIDECORNER][NORMAL] = load_bitmap("img/shore/grass/insidecorner.bmp", palette);
  images[IMG_SHORE_GRASS_OUTSIDECORNER][NORMAL] = load_bitmap("img/shore/grass/outsidecorner.bmp", palette);
  images[IMG_SHORE_GRASS_SHORE][NORMAL] = load_bitmap("img/shore/grass/shore.bmp", palette);
  images[IMG_HELP][NORMAL] = load_bitmap("img/help.bmp", palette);
  images[IMG_GAMEOVER][NORMAL] = load_bitmap("img/gameover.bmp", palette);
  images[IMG_NINJA_2][NORMAL] = load_bitmap("img/ninja/2.bmp", palette);
  images[IMG_NINJA_3][NORMAL] = load_bitmap("img/ninja/3.bmp", palette);
  images[IMG_NINJA_1][NORMAL] = load_bitmap("img/ninja/1.bmp", palette);

  /**
   * Load the palette last to get the correct colors.
   */
  images[IMG_PALETTE][NORMAL] = load_bitmap("img/palette.bmp", palette);

  /**
   * Load the sounds.
   */
  sounds[SND_SWORD] = load_sample("snd/sword.wav");
  sounds[SND_ARROW_HIT] = load_sample("snd/arrow/hit.wav");
  sounds[SND_ARROW_FLY] = load_sample("snd/arrow/fly.wav");
  sounds[SND_GASP] = load_sample("snd/gasp.wav");
  sounds[SND_CHOMP] = load_sample("snd/chomp.wav");
  sounds[SND_MONEY] = load_sample("snd/money.wav");
  sounds[SND_HEART] = load_sample("snd/heart.wav");
  sounds[SND_HAMMER] = load_sample("snd/hammer.wav");

  resources_initialized = ON;

  /**
   * Check to see if any resources failed to load.
   */
  for (i = 0; i < NUM_IMAGES; i++) {
    if (images[i][NORMAL] == NULL) {
      fprintf(stderr, "Failed to load image resource %d. \n", i);
      stop_resources();
      return OFF;
    }
  }

  for (i = 0; i < NUM_SOUNDS; i++) {
    if (sounds[i] == NULL) {
      fprintf(stderr, "Failed to load sound resource %d. \n", i);
      stop_resources();
      return OFF;
    }
  }
  
  return ON;
}




void stop_resources()
{
  int i;
  int j;

  if (!resources_initialized) {
    return;
  }

  for (i = 0; i < NUM_IMAGES; i++) {
    for (j = 0; j < NUM_IMAGE_FORMATS; j++) {
      destroy_bitmap(images[i][j]);
    }
  }

  for (i = 0; i < NUM_SOUNDS; i++) {
    destroy_sample(sounds[i]);
  }

  resources_initialized = OFF;
}




BITMAP *grab_image(int image, int format)
{
  if (images[image][format] == NULL) {
    load_formatted_image(image, format);
  }
  
  return images[image][format];
}




SAMPLE *grab_sound(int sound)
{
  return sounds[sound];
}




PALETTE *grab_color_palette()
{
  return &palette;
}
