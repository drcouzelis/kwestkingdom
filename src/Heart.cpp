#include "Character.h"
#include "Heart.h"
#include "resources.h"


Heart::Heart() {
  init_anim(&heart_anim, OFF, 0);
  add_frame(&heart_anim, IMG("heart.bmp"));

  anim = &heart_anim;
}


void Heart::collectedBy(Character *character) {
  character->setHealth(character->getHealth() + 1);
  play_sound(SND("heart.wav"));
}

