#include "Animation.h"
#include "Character.h"
#include "Heart.h"
#include "resources.h"


Heart::Heart() {
  animation = new Animation();
  animation->addFrame(IMG("heart.bmp"));
}


void Heart::collectedBy(Character *character) {
  character->setHealth(character->getHealth() + 1);
  play_sound(SND("heart.wav"));
}

