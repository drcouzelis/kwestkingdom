#ifndef STORYWORLD_HEADER
#define STORYWORLD_HEADER


#include "World.h"


class StoryWorld : public World {
public:
  StoryWorld();

  void update();
  void changeRooms();
};


#endif
