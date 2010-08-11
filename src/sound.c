#include "sound.h"



void play_sound(SAMPLE *sound)
{
  play_sample(sound, 255, 128, 1000, 0);
}




#define GAME_VOLUME 192




void toggle_sound()
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




FLAG is_sound_enabled()
{
  int digiVolume;
  int midiVolume;

  get_volume(&digiVolume, &midiVolume);

  if (digiVolume == 0) {
    return OFF;
  }

  return ON;
}
