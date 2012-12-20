#include "Animation.h"
#include "Character.h"
#include "Heart.h"
#include "Resources.h"


Heart::Heart() {
  animation = new Animation();
  animation->addFrame(IMG("HEART"));
}


void Heart::collectedBy(Character *character) {
  character->setHealth(character->getHealth() + 1);
  playSound(SOUNDS_HEART);
}

