#import "Resources.h"


BOOL initializedResources = NO;

BITMAP *images[NUMBER_OF_IMAGES];
SAMPLE *sounds[NUMBER_OF_SOUNDS];
PALETTE palette;


void initializeResources() {

  int i;

  if (initializedResources) {
    return;
  }

  images[IMG_SWORD_STAB_2] = load_bitmap("img/sword/stab/2.bmp", palette);
  images[IMG_SWORD_STAB_4] = load_bitmap("img/sword/stab/4.bmp", palette);
  images[IMG_SWORD_STAB_3] = load_bitmap("img/sword/stab/3.bmp", palette);
  images[IMG_SWORD_STAB_1] = load_bitmap("img/sword/stab/1.bmp", palette);
  images[IMG_SWORD_HOLD_2] = load_bitmap("img/sword/hold/2.bmp", palette);
  images[IMG_SWORD_HOLD_4] = load_bitmap("img/sword/hold/4.bmp", palette);
  images[IMG_SWORD_HOLD_3] = load_bitmap("img/sword/hold/3.bmp", palette);
  images[IMG_SWORD_HOLD_1] = load_bitmap("img/sword/hold/1.bmp", palette);
  images[IMG_SHIELD_2] = load_bitmap("img/shield/2.bmp", palette);
  images[IMG_SHIELD_4] = load_bitmap("img/shield/4.bmp", palette);
  images[IMG_SHIELD_3] = load_bitmap("img/shield/3.bmp", palette);
  images[IMG_SHIELD_1] = load_bitmap("img/shield/1.bmp", palette);
  images[IMG_TITLE] = load_bitmap("img/title.bmp", palette);
  images[IMG_CHOMPER_BITE_2] = load_bitmap("img/chomper/bite/2.bmp", palette);
  images[IMG_CHOMPER_BITE_4] = load_bitmap("img/chomper/bite/4.bmp", palette);
  images[IMG_CHOMPER_BITE_5] = load_bitmap("img/chomper/bite/5.bmp", palette);
  images[IMG_CHOMPER_BITE_3] = load_bitmap("img/chomper/bite/3.bmp", palette);
  images[IMG_CHOMPER_BITE_1] = load_bitmap("img/chomper/bite/1.bmp", palette);
  images[IMG_CHOMPER_STAND_2] = load_bitmap("img/chomper/stand/2.bmp", palette);
  images[IMG_CHOMPER_STAND_3] = load_bitmap("img/chomper/stand/3.bmp", palette);
  images[IMG_CHOMPER_STAND_1] = load_bitmap("img/chomper/stand/1.bmp", palette);
  images[IMG_HERO_HURT_2] = load_bitmap("img/hero/hurt/2.bmp", palette);
  images[IMG_HERO_HURT_4] = load_bitmap("img/hero/hurt/4.bmp", palette);
  images[IMG_HERO_HURT_3] = load_bitmap("img/hero/hurt/3.bmp", palette);
  images[IMG_HERO_HURT_1] = load_bitmap("img/hero/hurt/1.bmp", palette);
  images[IMG_HERO_DIE_2] = load_bitmap("img/hero/die/2.bmp", palette);
  images[IMG_HERO_DIE_4] = load_bitmap("img/hero/die/4.bmp", palette);
  images[IMG_HERO_DIE_5] = load_bitmap("img/hero/die/5.bmp", palette);
  images[IMG_HERO_DIE_3] = load_bitmap("img/hero/die/3.bmp", palette);
  images[IMG_HERO_DIE_1] = load_bitmap("img/hero/die/1.bmp", palette);
  images[IMG_HERO_ATTACK_2] = load_bitmap("img/hero/attack/2.bmp", palette);
  images[IMG_HERO_ATTACK_4] = load_bitmap("img/hero/attack/4.bmp", palette);
  images[IMG_HERO_ATTACK_3] = load_bitmap("img/hero/attack/3.bmp", palette);
  images[IMG_HERO_ATTACK_1] = load_bitmap("img/hero/attack/1.bmp", palette);
  images[IMG_HERO_STAND_2] = load_bitmap("img/hero/stand/2.bmp", palette);
  images[IMG_HERO_STAND_3] = load_bitmap("img/hero/stand/3.bmp", palette);
  images[IMG_HERO_STAND_1] = load_bitmap("img/hero/stand/1.bmp", palette);
  images[IMG_ARCHER_2] = load_bitmap("img/archer/2.bmp", palette);
  images[IMG_ARCHER_3] = load_bitmap("img/archer/3.bmp", palette);
  images[IMG_ARCHER_1] = load_bitmap("img/archer/1.bmp", palette);
  images[IMG_ITEMS_EMPTYHEART] = load_bitmap("img/items/emptyheart.bmp", palette);
  images[IMG_ITEMS_HEART] = load_bitmap("img/items/heart.bmp", palette);
  images[IMG_ITEMS_MONEYBAG] = load_bitmap("img/items/moneybag.bmp", palette);
  images[IMG_TERRAIN_DOWNSTAIRS] = load_bitmap("img/terrain/downstairs.bmp", palette);
  images[IMG_TERRAIN_WATER] = load_bitmap("img/terrain/water.bmp", palette);
  images[IMG_TERRAIN_DIRT] = load_bitmap("img/terrain/dirt.bmp", palette);
  images[IMG_TERRAIN_ICE] = load_bitmap("img/terrain/ice.bmp", palette);
  images[IMG_TERRAIN_PATH] = load_bitmap("img/terrain/path.bmp", palette);
  images[IMG_TERRAIN_SPIRE] = load_bitmap("img/terrain/spire.bmp", palette);
  images[IMG_TERRAIN_OAK] = load_bitmap("img/terrain/oak.bmp", palette);
  images[IMG_TERRAIN_UPSTAIRS] = load_bitmap("img/terrain/upstairs.bmp", palette);
  images[IMG_TERRAIN_SNOW] = load_bitmap("img/terrain/snow.bmp", palette);
  images[IMG_TERRAIN_EVERGREEN] = load_bitmap("img/terrain/evergreen.bmp", palette);
  images[IMG_TERRAIN_GRASS] = load_bitmap("img/terrain/grass.bmp", palette);
  images[IMG_HAMMER_SWING_2] = load_bitmap("img/hammer/swing/2.bmp", palette);
  images[IMG_HAMMER_SWING_4] = load_bitmap("img/hammer/swing/4.bmp", palette);
  images[IMG_HAMMER_SWING_3] = load_bitmap("img/hammer/swing/3.bmp", palette);
  images[IMG_HAMMER_SWING_1] = load_bitmap("img/hammer/swing/1.bmp", palette);
  images[IMG_HAMMER_HOLD_2] = load_bitmap("img/hammer/hold/2.bmp", palette);
  images[IMG_HAMMER_HOLD_4] = load_bitmap("img/hammer/hold/4.bmp", palette);
  images[IMG_HAMMER_HOLD_3] = load_bitmap("img/hammer/hold/3.bmp", palette);
  images[IMG_HAMMER_HOLD_1] = load_bitmap("img/hammer/hold/1.bmp", palette);
  images[IMG_BOW_DRAW_2] = load_bitmap("img/bow/draw/2.bmp", palette);
  images[IMG_BOW_DRAW_3] = load_bitmap("img/bow/draw/3.bmp", palette);
  images[IMG_BOW_DRAW_1] = load_bitmap("img/bow/draw/1.bmp", palette);
  images[IMG_BOW_HOLD_2] = load_bitmap("img/bow/hold/2.bmp", palette);
  images[IMG_BOW_HOLD_4] = load_bitmap("img/bow/hold/4.bmp", palette);
  images[IMG_BOW_HOLD_3] = load_bitmap("img/bow/hold/3.bmp", palette);
  images[IMG_BOW_HOLD_1] = load_bitmap("img/bow/hold/1.bmp", palette);
  images[IMG_GIANT_2] = load_bitmap("img/giant/2.bmp", palette);
  images[IMG_GIANT_3] = load_bitmap("img/giant/3.bmp", palette);
  images[IMG_GIANT_1] = load_bitmap("img/giant/1.bmp", palette);
  images[IMG_ARROW] = load_bitmap("img/arrow.bmp", palette);
  images[IMG_SHORE_SNOW_INSIDECORNER] = load_bitmap("img/shore/snow/insidecorner.bmp", palette);
  images[IMG_SHORE_SNOW_OUTSIDECORNER] = load_bitmap("img/shore/snow/outsidecorner.bmp", palette);
  images[IMG_SHORE_SNOW_SHORE] = load_bitmap("img/shore/snow/shore.bmp", palette);
  images[IMG_SHORE_GRASS_INSIDECORNER] = load_bitmap("img/shore/grass/insidecorner.bmp", palette);
  images[IMG_SHORE_GRASS_OUTSIDECORNER] = load_bitmap("img/shore/grass/outsidecorner.bmp", palette);
  images[IMG_SHORE_GRASS_SHORE] = load_bitmap("img/shore/grass/shore.bmp", palette);
  images[IMG_HELP] = load_bitmap("img/help.bmp", palette);
  images[IMG_GAMEOVER] = load_bitmap("img/gameover.bmp", palette);
  images[IMG_NINJA_2] = load_bitmap("img/ninja/2.bmp", palette);
  images[IMG_NINJA_3] = load_bitmap("img/ninja/3.bmp", palette);
  images[IMG_NINJA_1] = load_bitmap("img/ninja/1.bmp", palette);

  // Load the palette last to get the correct colors.
  images[IMG_PALETTE] = load_bitmap("img/palette.bmp", palette);

  // Load the sounds.
  sounds[SND_SWORD] = load_sample("snd/sword.wav");
  sounds[SND_ARROW_HIT] = load_sample("snd/arrow/hit.wav");
  sounds[SND_ARROW_FLY] = load_sample("snd/arrow/fly.wav");
  sounds[SND_GASP] = load_sample("snd/gasp.wav");
  sounds[SND_CHOMP] = load_sample("snd/chomp.wav");
  sounds[SND_MONEY] = load_sample("snd/money.wav");
  sounds[SND_HEART] = load_sample("snd/heart.wav");
  sounds[SND_HAMMER] = load_sample("snd/hammer.wav");

  initializedResources = YES;

  for (i = 0; i < NUMBER_OF_IMAGES; i++) {
    if (images[i] == NULL) {
      initializedResources = NO;
      destroyResources();
      return;
    }
  }

  for (i = 0; i < NUMBER_OF_SOUNDS; i++) {
    if (sounds[i] == NULL) {
      initializedResources = NO;
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

  initializedResources = NO;

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


BOOL soundEnabled(void) {

  int digiVolume;
  int midiVolume;

  get_volume(&digiVolume, &midiVolume);

  if (digiVolume == 0) {
    return NO;
  }

  return YES;

}

