#include "Resources.h"


bool initializedResources = false;

BITMAP *images[NUMBER_OF_IMAGES];
SAMPLE *sounds[NUMBER_OF_SOUNDS];
PALETTE palette;


void initializeResources() {
  
  int i;

  if (initializedResources) {
    return;
  }
  
  images[IMAGES_HERO_ATTACK_3] = load_bitmap( PKGDATADIR "/images/hero_attack_3.bmp", palette);
  images[IMAGES_BOW_HOLD_2] = load_bitmap( PKGDATADIR "/images/bow_hold_2.bmp", palette);
  images[IMAGES_HAMMER_SWING_3] = load_bitmap( PKGDATADIR "/images/hammer_swing_3.bmp", palette);
  images[IMAGES_GAMEOVER] = load_bitmap( PKGDATADIR "/images/gameover.bmp", palette);
  images[IMAGES_CHOMPER_STAND_1] = load_bitmap( PKGDATADIR "/images/chomper_stand_1.bmp", palette);
  images[IMAGES_BOW_HOLD_3] = load_bitmap( PKGDATADIR "/images/bow_hold_3.bmp", palette);
  images[IMAGES_TERRAIN_ICE] = load_bitmap( PKGDATADIR "/images/terrain_ice.bmp", palette);
  images[IMAGES_GIANT_2] = load_bitmap( PKGDATADIR "/images/giant_2.bmp", palette);
  images[IMAGES_HAMMER_HOLD_2] = load_bitmap( PKGDATADIR "/images/hammer_hold_2.bmp", palette);
  images[IMAGES_SWORD_STAB_4] = load_bitmap( PKGDATADIR "/images/sword_stab_4.bmp", palette);
  images[IMAGES_ARCHER_1] = load_bitmap( PKGDATADIR "/images/archer_1.bmp", palette);
  images[IMAGES_NINJA_1] = load_bitmap( PKGDATADIR "/images/ninja_1.bmp", palette);
  images[IMAGES_HERO_HURT_1] = load_bitmap( PKGDATADIR "/images/hero_hurt_1.bmp", palette);
  images[IMAGES_HERO_STAND_3] = load_bitmap( PKGDATADIR "/images/hero_stand_3.bmp", palette);
  images[IMAGES_BOW_DRAW_2] = load_bitmap( PKGDATADIR "/images/bow_draw_2.bmp", palette);
  images[IMAGES_HERO_DIE_4] = load_bitmap( PKGDATADIR "/images/hero_die_4.bmp", palette);
  images[IMAGES_TERRAIN_WATER] = load_bitmap( PKGDATADIR "/images/terrain_water.bmp", palette);
  images[IMAGES_ARROW] = load_bitmap( PKGDATADIR "/images/arrow.bmp", palette);
  images[IMAGES_SWORD_HOLD_4] = load_bitmap( PKGDATADIR "/images/sword_hold_4.bmp", palette);
  images[IMAGES_GIANT_1] = load_bitmap( PKGDATADIR "/images/giant_1.bmp", palette);
  images[IMAGES_ARCHER_2] = load_bitmap( PKGDATADIR "/images/archer_2.bmp", palette);
  images[IMAGES_NINJA_2] = load_bitmap( PKGDATADIR "/images/ninja_2.bmp", palette);
  images[IMAGES_HAMMER_HOLD_1] = load_bitmap( PKGDATADIR "/images/hammer_hold_1.bmp", palette);
  images[IMAGES_HERO_STAND_1] = load_bitmap( PKGDATADIR "/images/hero_stand_1.bmp", palette);
  images[IMAGES_BOW_HOLD_4] = load_bitmap( PKGDATADIR "/images/bow_hold_4.bmp", palette);
  images[IMAGES_TERRAIN_DIRT] = load_bitmap( PKGDATADIR "/images/terrain_dirt.bmp", palette);
  images[IMAGES_SWORD_STAB_2] = load_bitmap( PKGDATADIR "/images/sword_stab_2.bmp", palette);
  images[IMAGES_SHIELD_3] = load_bitmap( PKGDATADIR "/images/shield_3.bmp", palette);
  images[IMAGES_TITLE] = load_bitmap( PKGDATADIR "/images/title.bmp", palette);
  images[IMAGES_SHORE_SNOW] = load_bitmap( PKGDATADIR "/images/shore_snow.bmp", palette);
  images[IMAGES_HERO_HURT_3] = load_bitmap( PKGDATADIR "/images/hero_hurt_3.bmp", palette);
  images[IMAGES_HERO_DIE_3] = load_bitmap( PKGDATADIR "/images/hero_die_3.bmp", palette);
  images[IMAGES_TERRAIN_SNOW] = load_bitmap( PKGDATADIR "/images/terrain_snow.bmp", palette);
  images[IMAGES_CHOMPER_BITE_2] = load_bitmap( PKGDATADIR "/images/chomper_bite_2.bmp", palette);
  images[IMAGES_SHORE_SNOW_OUTSIDECORNER] = load_bitmap( PKGDATADIR "/images/shore_snow_outsidecorner.bmp", palette);
  images[IMAGES_ARCHER_3] = load_bitmap( PKGDATADIR "/images/archer_3.bmp", palette);
  images[IMAGES_CHOMPER_BITE_5] = load_bitmap( PKGDATADIR "/images/chomper_bite_5.bmp", palette);
  images[IMAGES_HERO_DIE_2] = load_bitmap( PKGDATADIR "/images/hero_die_2.bmp", palette);
  images[IMAGES_CHOMPER_STAND_2] = load_bitmap( PKGDATADIR "/images/chomper_stand_2.bmp", palette);
  images[IMAGES_HAMMER_HOLD_3] = load_bitmap( PKGDATADIR "/images/hammer_hold_3.bmp", palette);
  images[IMAGES_CHOMPER_BITE_3] = load_bitmap( PKGDATADIR "/images/chomper_bite_3.bmp", palette);
  images[IMAGES_HERO_ATTACK_1] = load_bitmap( PKGDATADIR "/images/hero_attack_1.bmp", palette);
  images[IMAGES_GIANT_3] = load_bitmap( PKGDATADIR "/images/giant_3.bmp", palette);
  images[IMAGES_SWORD_HOLD_1] = load_bitmap( PKGDATADIR "/images/sword_hold_1.bmp", palette);
  images[IMAGES_HERO_DIE_5] = load_bitmap( PKGDATADIR "/images/hero_die_5.bmp", palette);
  images[IMAGES_HAMMER_SWING_1] = load_bitmap( PKGDATADIR "/images/hammer_swing_1.bmp", palette);
  images[IMAGES_TERRAIN_SPIRE] = load_bitmap( PKGDATADIR "/images/terrain_spire.bmp", palette);
  images[IMAGES_BOW_DRAW_3] = load_bitmap( PKGDATADIR "/images/bow_draw_3.bmp", palette);
  images[IMAGES_SHORE_GRASS] = load_bitmap( PKGDATADIR "/images/shore_grass.bmp", palette);
  images[IMAGES_HERO_DIE_1] = load_bitmap( PKGDATADIR "/images/hero_die_1.bmp", palette);
  images[IMAGES_SWORD_HOLD_3] = load_bitmap( PKGDATADIR "/images/sword_hold_3.bmp", palette);
  images[IMAGES_HERO_HURT_4] = load_bitmap( PKGDATADIR "/images/hero_hurt_4.bmp", palette);
  images[IMAGES_SHIELD_2] = load_bitmap( PKGDATADIR "/images/shield_2.bmp", palette);
  images[IMAGES_TERRAIN_EVERGREEN] = load_bitmap( PKGDATADIR "/images/terrain_evergreen.bmp", palette);
  images[IMAGES_SWORD_STAB_1] = load_bitmap( PKGDATADIR "/images/sword_stab_1.bmp", palette);
  images[IMAGES_TERRAIN_DOWNSTAIRS] = load_bitmap( PKGDATADIR "/images/terrain_downstairs.bmp", palette);
  images[IMAGES_HAMMER_SWING_4] = load_bitmap( PKGDATADIR "/images/hammer_swing_4.bmp", palette);
  images[IMAGES_HERO_STAND_2] = load_bitmap( PKGDATADIR "/images/hero_stand_2.bmp", palette);
  images[IMAGES_BOW_DRAW_1] = load_bitmap( PKGDATADIR "/images/bow_draw_1.bmp", palette);
  images[IMAGES_HAMMER_HOLD_4] = load_bitmap( PKGDATADIR "/images/hammer_hold_4.bmp", palette);
  images[IMAGES_SWORD_STAB_3] = load_bitmap( PKGDATADIR "/images/sword_stab_3.bmp", palette);
  images[IMAGES_BOW_HOLD_1] = load_bitmap( PKGDATADIR "/images/bow_hold_1.bmp", palette);
  images[IMAGES_TERRAIN_GRASS] = load_bitmap( PKGDATADIR "/images/terrain_grass.bmp", palette);
  images[IMAGES_SWORD_HOLD_2] = load_bitmap( PKGDATADIR "/images/sword_hold_2.bmp", palette);
  images[IMAGES_CHOMPER_STAND_3] = load_bitmap( PKGDATADIR "/images/chomper_stand_3.bmp", palette);
  images[IMAGES_SHORE_SNOW_INSIDECORNER] = load_bitmap( PKGDATADIR "/images/shore_snow_insidecorner.bmp", palette);
  images[IMAGES_SHIELD_1] = load_bitmap( PKGDATADIR "/images/shield_1.bmp", palette);
  images[IMAGES_TERRAIN_OAK] = load_bitmap( PKGDATADIR "/images/terrain_oak.bmp", palette);
  images[IMAGES_HAMMER_SWING_2] = load_bitmap( PKGDATADIR "/images/hammer_swing_2.bmp", palette);
  images[IMAGES_HERO_ATTACK_4] = load_bitmap( PKGDATADIR "/images/hero_attack_4.bmp", palette);
  images[IMAGES_HERO_ATTACK_2] = load_bitmap( PKGDATADIR "/images/hero_attack_2.bmp", palette);
  images[IMAGES_HERO_HURT_2] = load_bitmap( PKGDATADIR "/images/hero_hurt_2.bmp", palette);
  images[IMAGES_HELP] = load_bitmap( PKGDATADIR "/images/help.bmp", palette);
  images[IMAGES_TERRAIN_UPSTAIRS] = load_bitmap( PKGDATADIR "/images/terrain_upstairs.bmp", palette);
  images[IMAGES_EMPTYHEART] = load_bitmap( PKGDATADIR "/images/emptyheart.bmp", palette);
  images[IMAGES_HEART] = load_bitmap( PKGDATADIR "/images/heart.bmp", palette);
  images[IMAGES_CHOMPER_BITE_4] = load_bitmap( PKGDATADIR "/images/chomper_bite_4.bmp", palette);
  images[IMAGES_NINJA_3] = load_bitmap( PKGDATADIR "/images/ninja_3.bmp", palette);
  images[IMAGES_SHORE_GRASS_OUTSIDECORNER] = load_bitmap( PKGDATADIR "/images/shore_grass_outsidecorner.bmp", palette);
  images[IMAGES_CHOMPER_BITE_1] = load_bitmap( PKGDATADIR "/images/chomper_bite_1.bmp", palette);
  images[IMAGES_MONEYBAG] = load_bitmap( PKGDATADIR "/images/moneybag.bmp", palette);
  images[IMAGES_SHORE_GRASS_INSIDECORNER] = load_bitmap( PKGDATADIR "/images/shore_grass_insidecorner.bmp", palette);
  images[IMAGES_SHIELD_4] = load_bitmap( PKGDATADIR "/images/shield_4.bmp", palette);
  images[IMAGES_TERRAIN_PATH] = load_bitmap( PKGDATADIR "/images/terrain_path.bmp", palette);

  // Load the palette last to get the correct colors.
  images[IMAGES_PALETTE] = load_bitmap( PKGDATADIR "/images/palette.bmp", palette);

  // Load the sounds.
  sounds[SOUNDS_SWORD] = load_sample( PKGDATADIR "/sounds/sword.wav");
  sounds[SOUNDS_ARROW_HIT] = load_sample( PKGDATADIR "/sounds/arrow_hit.wav");
  sounds[SOUNDS_ARROW_FLY] = load_sample( PKGDATADIR "/sounds/arrow_fly.wav");
  sounds[SOUNDS_GASP] = load_sample( PKGDATADIR "/sounds/gasp.wav");
  sounds[SOUNDS_CHOMP] = load_sample( PKGDATADIR "/sounds/chomp.wav");
  sounds[SOUNDS_MONEY] = load_sample( PKGDATADIR "/sounds/money.wav");
  sounds[SOUNDS_HEART] = load_sample( PKGDATADIR "/sounds/heart.wav");
  sounds[SOUNDS_HAMMER] = load_sample( PKGDATADIR "/sounds/hammer.wav");

  initializedResources = true;

  for (i = 0; i < NUMBER_OF_IMAGES; i++) {
    if (images[i] == NULL) {
      initializedResources = false;
      destroyResources();
      return;
    }
  }
  
  for (i = 0; i < NUMBER_OF_SOUNDS; i++) {
    if (sounds[i] == NULL) {
      initializedResources = false;
      destroyResources();
      return;
    }
  }

}


void destroyResources() {

  int i;

  if (!initializedResources) {
    return;
  }

  for (i = 0; i < NUMBER_OF_IMAGES; i++) {
    destroy_bitmap(images[i]);
  }

  for (i = 0; i < NUMBER_OF_SOUNDS; i++) {
    destroy_sample(sounds[i]);
  }

  initializedResources = false;

}


BITMAP * getImage(int image) {
  return images[image];
}


void setPalette(void) {
  set_palette(palette);
}


void playSound(int sound) {
  play_sample(sounds[sound], 255, 128, 1000, 0);
}


#define GAME_VOLUME 192


void toggleSound(void) {
  
  int digiVolume;
  int midiVolume;
  
  get_volume(&digiVolume, &midiVolume);
  
  if (digiVolume == 0) {
    set_volume(GAME_VOLUME, GAME_VOLUME);
  } else {
    set_volume(0, 0);
  }
  
}


bool soundEnabled(void) {
  
  int digiVolume;
  int midiVolume;
  
  get_volume(&digiVolume, &midiVolume);
  
  if (digiVolume == 0) {
    return false;
  }
  
  return true;
  
}

