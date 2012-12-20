#include "Animation.h"
#include "HelpTile.h"
#include "Hero.h"
#include "RoomFactory.h"
#include "Snapshot.h"
#include "StoryWorld.h"


#define MAX_NUM_OF_ROOMS 40

// The max size of a help line is 32 characters.

// Welcome
#define WELCOME_TEXT_LINE_1 "Welcome to KWEST KINGDOM!"
#define WELCOME_TEXT_LINE_2 "These HELP TILES will"
#define WELCOME_TEXT_LINE_3 "give you HINTS."

// About
#define ABOUT_TEXT_LINE_1 "This is a TURN-BASED STRATEGY"
#define ABOUT_TEXT_LINE_2 "game. ENEMIES will MOVE AFTER"
#define ABOUT_TEXT_LINE_3 "YOU move or use an item."

// Shield
#define SHIELD_TEXT_LINE_1 "Press \"1\" to draw your SHIELD."
#define SHIELD_TEXT_LINE_2 "You will BLOCK all ATTACKS from"
#define SHIELD_TEXT_LINE_3 "enemies, but you will move more"
#define SHIELD_TEXT_LINE_4 "slowly. Enemies will move twice"
#define SHIELD_TEXT_LINE_5 "after you move once."

// Sword
#define SWORD_TEXT_LINE_1 "Press \"2\" to draw your SWORD."
#define SWORD_TEXT_LINE_2 "Hold \"CTRL\" and press a"
#define SWORD_TEXT_LINE_3 "DIRECTION KEY to ATTACK. You"
#define SWORD_TEXT_LINE_4 "do not need to hold \"CTRL\" if"
#define SWORD_TEXT_LINE_5 "you are standing next to an"
#define SWORD_TEXT_LINE_6 "enemy."

// Bow
#define BOW_TEXT_LINE_1 "Press \"3\" to draw your BOW."
#define BOW_TEXT_LINE_2 "Hold \"CTRL\" and press a"
#define BOW_TEXT_LINE_3 "DIRECTION KEY to shoot an"
#define BOW_TEXT_LINE_4 "ARROW. Enemies will move twice"
#define BOW_TEXT_LINE_5 "as you draw an arrow and shoot"
#define BOW_TEXT_LINE_6 "it."

// Wait
#define WAIT_TEXT_LINE_1 "Press SPACEBAR to SKIP A TURN"
#define WAIT_TEXT_LINE_2 "and wait for enemies to move."
#define WAIT_TEXT_LINE_3 "How can this help you attack"
#define WAIT_TEXT_LINE_4 "your enemies?"

// Chomper
#define CHOMPER_TEXT_LINE_1 "Be careful! Do not get bitten by"
#define CHOMPER_TEXT_LINE_2 "a brown CHOMPER! They will chase"
#define CHOMPER_TEXT_LINE_3 "you when you are NEARBY and try"
#define CHOMPER_TEXT_LINE_4 "to BITE you."

// Archer
#define ARCHER_TEXT_LINE_1 "Look out! A green ARCHER will"
#define ARCHER_TEXT_LINE_2 "draw an ARROW and SHOOT it to"
#define ARCHER_TEXT_LINE_3 "try and hit you."

// Ninja
#define NINJA_TEXT_LINE_1 "A sneaky red NINJA will DASH and ATTACK you"
#define NINJA_TEXT_LINE_2 "when he SEES you."

// Giant
#define GIANT_TEXT_LINE_1 "A GIANT will SMASH you with his"
#define GIANT_TEXT_LINE_2 "HAMMER when you are NEXT to him."
#define GIANT_TEXT_LINE_3 "Don't get flattened!"





StoryWorld::StoryWorld() {
  
  HelpTile *helpTile;
  
  roomFactory->setChanceOfChomper(0);
  roomFactory->setChanceOfArcher(0);
  roomFactory->setChanceOfNinja(0);
  roomFactory->setChanceOfGiant(0);
  
  // Welcome help
  helpTile = new HelpTile();
  helpTile->setX(room->getXOfStepNumber(2));
  helpTile->setY(room->getYOfStepNumber(2));
  helpTile->setLines((char *)WELCOME_TEXT_LINE_1,
                     (char *)WELCOME_TEXT_LINE_2,
                     (char *)WELCOME_TEXT_LINE_3,
                     (char *)NULL,
                     (char *)NULL,
                     (char *)NULL);
  this->addHelpTile(helpTile);
  
  // About help
  helpTile = new HelpTile();
  helpTile->setX(room->getXOfStepNumber(4));
  helpTile->setY(room->getYOfStepNumber(4));
  helpTile->setLines((char *)ABOUT_TEXT_LINE_1,
                     (char *)ABOUT_TEXT_LINE_2,
                     (char *)ABOUT_TEXT_LINE_3,
                     (char *)NULL,
                     (char *)NULL,
                     (char *)NULL);
  this->addHelpTile(helpTile);
  
  hero->emptyHands();
    
}


void StoryWorld::update() {
  
  World::update();
  
  // This will add the enemy to the room AFTER the room number that is shown here.
  if (room->getNumber() == 2) {
    roomFactory->setChanceOfChomper(DEFAULT_CHANCE_OF_CHOMPER);
    difficulty = 5;
  } else if (room->getNumber() == 5) {
    roomFactory->setChanceOfArcher(DEFAULT_CHANCE_OF_ARCHER);
  } else if (room->getNumber() == 8) {
    roomFactory->setChanceOfNinja(DEFAULT_CHANCE_OF_NINJA);
  } else if (room->getNumber() == 11) {
    roomFactory->setChanceOfGiant(DEFAULT_CHANCE_OF_GIANT);
  } else if (room->getNumber() == 16) {
    difficulty = 100;
  }
  
  if (room->getNumber() == MAX_NUM_OF_ROOMS) {
    // There are no more rooms to explore!
    // It's the end of the game.
    //play_sound(SND("sound.wav"));
    game_over();
  }
  

}


void StoryWorld::changeRooms() {
  
  HelpTile *helpTile;
  
  World::changeRooms();
  
  if (room->getNumber() == 2) {
    
    // Sword help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(2));
    helpTile->setY(room->getYOfStepNumber(2));
    helpTile->setLines((char *)SWORD_TEXT_LINE_1,
                       (char *)SWORD_TEXT_LINE_2,
                       (char *)SWORD_TEXT_LINE_3,
                       (char *)SWORD_TEXT_LINE_4,
                       (char *)SWORD_TEXT_LINE_5,
                       (char *)SWORD_TEXT_LINE_6);
    this->addHelpTile(helpTile);
    
    // Chomper help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setY(room->getYOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setLines((char *)CHOMPER_TEXT_LINE_1,
                       (char *)CHOMPER_TEXT_LINE_2,
                       (char *)CHOMPER_TEXT_LINE_3,
                       (char *)CHOMPER_TEXT_LINE_4,
                       (char *)NULL,
                       (char *)NULL);
    this->addHelpTile(helpTile);
    
  } else if (room->getNumber() == 3) {
    
    // Wait help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(2));
    helpTile->setY(room->getYOfStepNumber(2));
    helpTile->setLines((char *)WAIT_TEXT_LINE_1,
                       (char *)WAIT_TEXT_LINE_2,
                       (char *)WAIT_TEXT_LINE_3,
                       (char *)WAIT_TEXT_LINE_4,
                       (char *)NULL,
                       (char *)NULL);
    this->addHelpTile(helpTile);
    
  } else if (room->getNumber() == 4) {
    
    // Shield help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(2));
    helpTile->setY(room->getYOfStepNumber(2));
    helpTile->setLines((char *)SHIELD_TEXT_LINE_1,
                       (char *)SHIELD_TEXT_LINE_2,
                       (char *)SHIELD_TEXT_LINE_3,
                       (char *)SHIELD_TEXT_LINE_4,
                       (char *)SHIELD_TEXT_LINE_5,
                       (char *)NULL);
    this->addHelpTile(helpTile);
    
  } else if (room->getNumber() == 5) {
    
    // Bow help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(2));
    helpTile->setY(room->getYOfStepNumber(2));
    helpTile->setLines((char *)BOW_TEXT_LINE_1,
                       (char *)BOW_TEXT_LINE_2,
                       (char *)BOW_TEXT_LINE_3,
                       (char *)BOW_TEXT_LINE_4,
                       (char *)BOW_TEXT_LINE_5,
                       (char *)BOW_TEXT_LINE_6);
    this->addHelpTile(helpTile);
    
    // Archer help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setY(room->getXOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setLines((char *)ARCHER_TEXT_LINE_1,
                       (char *)ARCHER_TEXT_LINE_2,
                       (char *)ARCHER_TEXT_LINE_3,
                       (char *)NULL,
                       (char *)NULL,
                       (char *)NULL);
    this->addHelpTile(helpTile);
    
  } else if (room->getNumber() == 8) {
    
    // Ninja help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setY(room->getXOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setLines((char *)NINJA_TEXT_LINE_1,
                       (char *)NINJA_TEXT_LINE_2,
                       (char *)NULL,
                       (char *)NULL,
                       (char *)NULL,
                       (char *)NULL);
    this->addHelpTile(helpTile);
    
  } else if (room->getNumber() == 11) {
    
    // Giant help
    helpTile = new HelpTile();
    helpTile->setX(room->getXOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setY(room->getXOfStepNumber(room->getSizeOfPath() - 4));
    helpTile->setLines((char *)GIANT_TEXT_LINE_1,
                       (char *)GIANT_TEXT_LINE_2,
                       (char *)GIANT_TEXT_LINE_3,
                       (char *)NULL,
                       (char *)NULL,
                       (char *)NULL);
    this->addHelpTile(helpTile);
    
  }
  
  this->drawTerrain(nextRoomSnapshot->getCanvas());
  this->drawCharacters(nextRoomSnapshot->getCanvas());
}

