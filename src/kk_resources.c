#include "kk_resources.h"




static BITMAP *kk_images[KK_NUMBER_OF_IMAGES];
static SAMPLE *kk_sounds[KK_NUMBER_OF_SOUNDS];
static PALETTE kk_palette;

static bool kk_resources_are_initialized = false;




void kk_init_resources()
{
  int i;

  if (kk_resources_are_initialized) {
    return;
  }

  kk_images[KK_IMG_SWORD_STAB_2] = load_bitmap("img/sword/stab/2.bmp", kk_palette);
  kk_images[KK_IMG_SWORD_STAB_4] = load_bitmap("img/sword/stab/4.bmp", kk_palette);
  kk_images[KK_IMG_SWORD_STAB_3] = load_bitmap("img/sword/stab/3.bmp", kk_palette);
  kk_images[KK_IMG_SWORD_STAB_1] = load_bitmap("img/sword/stab/1.bmp", kk_palette);
  kk_images[KK_IMG_SWORD_HOLD_2] = load_bitmap("img/sword/hold/2.bmp", kk_palette);
  kk_images[KK_IMG_SWORD_HOLD_4] = load_bitmap("img/sword/hold/4.bmp", kk_palette);
  kk_images[KK_IMG_SWORD_HOLD_3] = load_bitmap("img/sword/hold/3.bmp", kk_palette);
  kk_images[KK_IMG_SWORD_HOLD_1] = load_bitmap("img/sword/hold/1.bmp", kk_palette);
  kk_images[KK_IMG_SHIELD_2] = load_bitmap("img/shield/2.bmp", kk_palette);
  kk_images[KK_IMG_SHIELD_4] = load_bitmap("img/shield/4.bmp", kk_palette);
  kk_images[KK_IMG_SHIELD_3] = load_bitmap("img/shield/3.bmp", kk_palette);
  kk_images[KK_IMG_SHIELD_1] = load_bitmap("img/shield/1.bmp", kk_palette);
  kk_images[KK_IMG_TITLE] = load_bitmap("img/title.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_BITE_2] = load_bitmap("img/chomper/bite/2.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_BITE_4] = load_bitmap("img/chomper/bite/4.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_BITE_5] = load_bitmap("img/chomper/bite/5.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_BITE_3] = load_bitmap("img/chomper/bite/3.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_BITE_1] = load_bitmap("img/chomper/bite/1.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_STAND_2] = load_bitmap("img/chomper/stand/2.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_STAND_3] = load_bitmap("img/chomper/stand/3.bmp", kk_palette);
  kk_images[KK_IMG_CHOMPER_STAND_1] = load_bitmap("img/chomper/stand/1.bmp", kk_palette);
  kk_images[KK_IMG_HERO_HURT_2] = load_bitmap("img/hero/hurt/2.bmp", kk_palette);
  kk_images[KK_IMG_HERO_HURT_4] = load_bitmap("img/hero/hurt/4.bmp", kk_palette);
  kk_images[KK_IMG_HERO_HURT_3] = load_bitmap("img/hero/hurt/3.bmp", kk_palette);
  kk_images[KK_IMG_HERO_HURT_1] = load_bitmap("img/hero/hurt/1.bmp", kk_palette);
  kk_images[KK_IMG_HERO_DIE_2] = load_bitmap("img/hero/die/2.bmp", kk_palette);
  kk_images[KK_IMG_HERO_DIE_4] = load_bitmap("img/hero/die/4.bmp", kk_palette);
  kk_images[KK_IMG_HERO_DIE_5] = load_bitmap("img/hero/die/5.bmp", kk_palette);
  kk_images[KK_IMG_HERO_DIE_3] = load_bitmap("img/hero/die/3.bmp", kk_palette);
  kk_images[KK_IMG_HERO_DIE_1] = load_bitmap("img/hero/die/1.bmp", kk_palette);
  kk_images[KK_IMG_HERO_ATTACK_2] = load_bitmap("img/hero/attack/2.bmp", kk_palette);
  kk_images[KK_IMG_HERO_ATTACK_4] = load_bitmap("img/hero/attack/4.bmp", kk_palette);
  kk_images[KK_IMG_HERO_ATTACK_3] = load_bitmap("img/hero/attack/3.bmp", kk_palette);
  kk_images[KK_IMG_HERO_ATTACK_1] = load_bitmap("img/hero/attack/1.bmp", kk_palette);
  kk_images[KK_IMG_HERO_STAND_2] = load_bitmap("img/hero/stand/2.bmp", kk_palette);
  kk_images[KK_IMG_HERO_STAND_3] = load_bitmap("img/hero/stand/3.bmp", kk_palette);
  kk_images[KK_IMG_HERO_STAND_1] = load_bitmap("img/hero/stand/1.bmp", kk_palette);
  kk_images[KK_IMG_ARCHER_2] = load_bitmap("img/archer/2.bmp", kk_palette);
  kk_images[KK_IMG_ARCHER_3] = load_bitmap("img/archer/3.bmp", kk_palette);
  kk_images[KK_IMG_ARCHER_1] = load_bitmap("img/archer/1.bmp", kk_palette);
  kk_images[KK_IMG_ITEMS_EMPTYHEART] = load_bitmap("img/items/emptyheart.bmp", kk_palette);
  kk_images[KK_IMG_ITEMS_HEART] = load_bitmap("img/items/heart.bmp", kk_palette);
  kk_images[KK_IMG_ITEMS_MONEYBAG] = load_bitmap("img/items/moneybag.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_DOWNSTAIRS] = load_bitmap("img/terrain/downstairs.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_WATER] = load_bitmap("img/terrain/water.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_DIRT] = load_bitmap("img/terrain/dirt.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_ICE] = load_bitmap("img/terrain/ice.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_PATH] = load_bitmap("img/terrain/path.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_SPIRE] = load_bitmap("img/terrain/spire.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_OAK] = load_bitmap("img/terrain/oak.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_UPSTAIRS] = load_bitmap("img/terrain/upstairs.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_SNOW] = load_bitmap("img/terrain/snow.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_EVERGREEN] = load_bitmap("img/terrain/evergreen.bmp", kk_palette);
  kk_images[KK_IMG_TERRAIN_GRASS] = load_bitmap("img/terrain/grass.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_SWING_2] = load_bitmap("img/hammer/swing/2.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_SWING_4] = load_bitmap("img/hammer/swing/4.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_SWING_3] = load_bitmap("img/hammer/swing/3.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_SWING_1] = load_bitmap("img/hammer/swing/1.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_HOLD_2] = load_bitmap("img/hammer/hold/2.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_HOLD_4] = load_bitmap("img/hammer/hold/4.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_HOLD_3] = load_bitmap("img/hammer/hold/3.bmp", kk_palette);
  kk_images[KK_IMG_HAMMER_HOLD_1] = load_bitmap("img/hammer/hold/1.bmp", kk_palette);
  kk_images[KK_IMG_BOW_DRAW_2] = load_bitmap("img/bow/draw/2.bmp", kk_palette);
  kk_images[KK_IMG_BOW_DRAW_3] = load_bitmap("img/bow/draw/3.bmp", kk_palette);
  kk_images[KK_IMG_BOW_DRAW_1] = load_bitmap("img/bow/draw/1.bmp", kk_palette);
  kk_images[KK_IMG_BOW_HOLD_2] = load_bitmap("img/bow/hold/2.bmp", kk_palette);
  kk_images[KK_IMG_BOW_HOLD_4] = load_bitmap("img/bow/hold/4.bmp", kk_palette);
  kk_images[KK_IMG_BOW_HOLD_3] = load_bitmap("img/bow/hold/3.bmp", kk_palette);
  kk_images[KK_IMG_BOW_HOLD_1] = load_bitmap("img/bow/hold/1.bmp", kk_palette);
  kk_images[KK_IMG_GIANT_2] = load_bitmap("img/giant/2.bmp", kk_palette);
  kk_images[KK_IMG_GIANT_3] = load_bitmap("img/giant/3.bmp", kk_palette);
  kk_images[KK_IMG_GIANT_1] = load_bitmap("img/giant/1.bmp", kk_palette);
  kk_images[KK_IMG_ARROW] = load_bitmap("img/arrow.bmp", kk_palette);
  kk_images[KK_IMG_SHORE_SNOW_INSIDECORNER] = load_bitmap("img/shore/snow/insidecorner.bmp", kk_palette);
  kk_images[KK_IMG_SHORE_SNOW_OUTSIDECORNER] = load_bitmap("img/shore/snow/outsidecorner.bmp", kk_palette);
  kk_images[KK_IMG_SHORE_SNOW_SHORE] = load_bitmap("img/shore/snow/shore.bmp", kk_palette);
  kk_images[KK_IMG_SHORE_GRASS_INSIDECORNER] = load_bitmap("img/shore/grass/insidecorner.bmp", kk_palette);
  kk_images[KK_IMG_SHORE_GRASS_OUTSIDECORNER] = load_bitmap("img/shore/grass/outsidecorner.bmp", kk_palette);
  kk_images[KK_IMG_SHORE_GRASS_SHORE] = load_bitmap("img/shore/grass/shore.bmp", kk_palette);
  kk_images[KK_IMG_HELP] = load_bitmap("img/help.bmp", kk_palette);
  kk_images[KK_IMG_GAMEOVER] = load_bitmap("img/gameover.bmp", kk_palette);
  kk_images[KK_IMG_NINJA_2] = load_bitmap("img/ninja/2.bmp", kk_palette);
  kk_images[KK_IMG_NINJA_3] = load_bitmap("img/ninja/3.bmp", kk_palette);
  kk_images[KK_IMG_NINJA_1] = load_bitmap("img/ninja/1.bmp", kk_palette);

  // Load the palette last to get the correct colors.
  kk_images[KK_IMG_PALETTE] = load_bitmap("img/palette.bmp", kk_palette);

  // Load the sounds.
  kk_sounds[KK_SND_SWORD] = load_sample("snd/sword.wav");
  kk_sounds[KK_SND_ARROW_HIT] = load_sample("snd/arrow/hit.wav");
  kk_sounds[KK_SND_ARROW_FLY] = load_sample("snd/arrow/fly.wav");
  kk_sounds[KK_SND_GASP] = load_sample("snd/gasp.wav");
  kk_sounds[KK_SND_CHOMP] = load_sample("snd/chomp.wav");
  kk_sounds[KK_SND_MONEY] = load_sample("snd/money.wav");
  kk_sounds[KK_SND_HEART] = load_sample("snd/heart.wav");
  kk_sounds[KK_SND_HAMMER] = load_sample("snd/hammer.wav");

  kk_resources_are_initialized = true;

  for (i = 0; i < KK_NUMBER_OF_IMAGES; i++) {
    if (kk_images[i] == NULL) {
      fprintf(stderr, "Failed to load image resource %d. \n", i);
      kk_free_resources();
      return;
    }
  }

  for (i = 0; i < KK_NUMBER_OF_SOUNDS; i++) {
    if (kk_sounds[i] == NULL) {
      fprintf(stderr, "Failed to load sound resource %d. \n", i);
      kk_free_resources();
      return;
    }
  }
}




void kk_free_resources()
{
  int i;

  if (!kk_resources_are_initialized) {
    return;
  }

  for (i = 0; i < KK_NUMBER_OF_IMAGES; i++) {
    destroy_bitmap(kk_images[i]);
  }

  for (i = 0; i < KK_NUMBER_OF_SOUNDS; i++) {
    destroy_sample(kk_sounds[i]);
  }

  kk_resources_are_initialized = false;
}




inline BITMAP * kk_get_image(int image)
{
  return kk_images[image];
}




PALETTE * kk_get_palette()
{
  return &kk_palette;
}




inline void kk_play_sound(int sound)
{
  play_sample(kk_sounds[sound], 255, 128, 1000, 0);
}




#define GAME_VOLUME 192




void kk_toggle_sound()
{
  int digiVolume;
  int midiVolume;

  get_volume(&digiVolume, &midiVolume);

  if (digiVolume == 0) {
    set_volume(GAME_VOLUME, GAME_VOLUME);
  } else {
    set_volume(0, 0);
  }
}




bool kk_sound_enabled()
{
  int digiVolume;
  int midiVolume;

  get_volume(&digiVolume, &midiVolume);

  if (digiVolume == 0) {
    return false;
  }

  return true;
}
