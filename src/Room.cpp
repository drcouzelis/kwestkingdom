#include "List.h"
#include "Room.h"


Room::Room() {
  
  int x;
  int y;
  int i;
  
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      path_map[x][y] = 0;
    }
  }

  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      terrain_map[x][y] = 0;
    }
  }
  
  enemies = new List();
  items = new List();
  helpTiles = new List();
  
  entranceFromNextRoomX = 0;
  entranceFromNextRoomY = 0;
  entranceFromPrevRoomX = 0;
  entranceFromPrevRoomY = 0;
  exitToNextRoomX = 0;
  exitToNextRoomY = 0;
  exitToPrevRoomX = 0;
  exitToPrevRoomY = 0;
  
  number = 0;
  
  init_anim(&grass_anim, OFF, 0);
  init_anim(&path_anim, OFF, 0);
  init_anim(&mountain_anim, OFF, 0);
  init_anim(&water_anim, OFF, 0);
  init_anim(&shore_north_anim, OFF, 0);
  init_anim(&shore_south_anim, OFF, 0);
  init_anim(&shore_east_anim, OFF, 0);
  init_anim(&shore_west_anim, OFF, 0);
  init_anim(&shore_inside_ne_anim, OFF, 0);
  init_anim(&shore_inside_nw_anim, OFF, 0);
  init_anim(&shore_inside_se_anim, OFF, 0);
  init_anim(&shore_inside_sw_anim, OFF, 0);
  init_anim(&shore_outside_ne_anim, OFF, 0);
  init_anim(&shore_outside_nw_anim, OFF, 0);
  init_anim(&shore_outside_se_anim, OFF, 0);
  init_anim(&shore_outside_sw_anim, OFF, 0);
  
  for (i = 0; i < MAX_NUM_OF_STEPS; i++) {
    path[i] = NO_STEP;
  }
  steps = 0;
}


Room::~Room() {
  delete enemies;
  delete items;
  delete helpTiles;
}


void Room::update() {
  animate(&grass_anim);
  animate(&path_anim);
  animate(&mountain_anim);
  animate(&water_anim);
  animate(&shore_north_anim);
  animate(&shore_south_anim);
  animate(&shore_east_anim);
  animate(&shore_west_anim);
  animate(&shore_inside_ne_anim);
  animate(&shore_inside_nw_anim);
  animate(&shore_inside_se_anim);
  animate(&shore_inside_sw_anim);
  animate(&shore_outside_ne_anim);
  animate(&shore_outside_nw_anim);
  animate(&shore_outside_se_anim);
  animate(&shore_outside_sw_anim);
}


void Room::draw(IMAGE * canvas) {
  
  int x;
  int y;
  
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      
      //if (path_map[x][y]) { // Draw the path
        //draw_anim(&path_anim, canvas, x * getTileSize(), y * getTileSize());
      //} else
      if (terrain_map[x][y] == GRASS_TERRAIN) {
        draw_anim(&grass_anim, canvas, x * getTileSize(), y * getTileSize());
      } else if (terrain_map[x][y] == TREE_TERRAIN) {
        draw_anim(&mountain_anim, canvas, x * getTileSize(), y * getTileSize());
      } else if (terrain_map[x][y] == WATER_TERRAIN) {
        
        draw_anim(&water_anim, canvas, x * getTileSize(), y * getTileSize());
        
        // Add the shore borders
        if (terrain_map[x][y - 1] != WATER_TERRAIN) { // North
          draw_anim(&shore_north_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (terrain_map[x][y + 1] != WATER_TERRAIN) { // South
          draw_anim(&shore_south_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (terrain_map[x + 1][y] != WATER_TERRAIN) { // East
          draw_anim(&shore_east_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (terrain_map[x - 1][y] != WATER_TERRAIN) { // West
          draw_anim(&shore_west_anim, canvas, x * getTileSize(), y * getTileSize());
        }
          
      }
      
    }
  }
  
  // Add the shore corners
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      
      if (terrain_map[x][y] == WATER_TERRAIN) {
        
        // Add the shore inside corners
        if (
          terrain_map[x][y - 1] != WATER_TERRAIN &&
          terrain_map[x + 1][y] != WATER_TERRAIN
        ) { // North East
          draw_anim(&shore_inside_ne_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (
          terrain_map[x][y + 1] != WATER_TERRAIN &&
          terrain_map[x + 1][y] != WATER_TERRAIN
        ) { // South East
          draw_anim(&shore_inside_se_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (
          terrain_map[x][y - 1] != WATER_TERRAIN &&
          terrain_map[x - 1][y] != WATER_TERRAIN
        ) { // North West
          draw_anim(&shore_inside_nw_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (
          terrain_map[x][y + 1] != WATER_TERRAIN &&
          terrain_map[x - 1][y] != WATER_TERRAIN
        ) { // South West
          draw_anim(&shore_inside_sw_anim, canvas, x * getTileSize(), y * getTileSize());
        }
          
        // Add the shore outside corners.
        if (
          terrain_map[x][y - 1] == WATER_TERRAIN &&
          terrain_map[x + 1][y] == WATER_TERRAIN &&
          terrain_map[x + 1][y - 1] != WATER_TERRAIN
        ) { // North East
          draw_anim(&shore_outside_ne_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (
          terrain_map[x][y + 1] == WATER_TERRAIN &&
          terrain_map[x + 1][y] == WATER_TERRAIN &&
          terrain_map[x + 1][y + 1] != WATER_TERRAIN
        ) { // South East
          draw_anim(&shore_outside_se_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (
          terrain_map[x][y - 1] == WATER_TERRAIN &&
          terrain_map[x - 1][y] == WATER_TERRAIN &&
          terrain_map[x - 1][y - 1] != WATER_TERRAIN
        ) { // North West
          draw_anim(&shore_outside_nw_anim, canvas, x * getTileSize(), y * getTileSize());
        }
        if (
          terrain_map[x][y + 1] == WATER_TERRAIN &&
          terrain_map[x - 1][y] == WATER_TERRAIN &&
          terrain_map[x - 1][y + 1] != WATER_TERRAIN
        ) { // South West
          draw_anim(&shore_outside_sw_anim, canvas, x * getTileSize(), y * getTileSize());
        }
      }
      
    }
  }
}


List * Room::getEnemies() {
  return enemies;
}


List * Room::getItems() {
  return items;
}


List * Room::getHelpTiles() {
  return helpTiles;
}


void Room::setNumber(int aNumber) {
  number = aNumber;

}


int Room::getNumber() {
  return number;
}


void Room::addStep(int aStep) {
  path[steps] = aStep;
  steps++;

}


int Room::getSizeOfPath() {
  return steps;
}


int Room::getXOfStepNumber(int aStep) {
  if (path[aStep] == NO_STEP) {
    return NO_STEP;
  }
  return path[aStep] - ((path[aStep] / COLS) * COLS);
}


int Room::getYOfStepNumber(int aStep) {
  if (path[aStep] == NO_STEP) {
    return NO_STEP;
  }
  return path[aStep] / COLS;
}


FLAG Room::isSwimmable(int x, int y) {
  return terrain_map[x][y] == WATER_TERRAIN ? ON : OFF;
}


FLAG Room::isWalkable(int x, int y) {
  return terrain_map[x][y] == GRASS_TERRAIN ? ON : OFF;
}


FLAG Room::isJumpable(int x, int y) {
  return !(terrain_map[x][y] == TREE_TERRAIN) ? ON : OFF;
}


FLAG Room::isFlyable(int x, int y) {
  return !(terrain_map[x][y] == TREE_TERRAIN) ? ON : OFF;
}


FLAG Room::isSoarable(int x, int y) {
  // You can soar above any type of terrain.
  return ON;
}


void Room::removeExitToPrevRoom() {
  terrain_map[entranceFromPrevRoomX][entranceFromPrevRoomY] = TREE_TERRAIN;
  this->setExitToPrevRoomX(-1);
  this->setExitToPrevRoomY(-1);

}


int Room::getEntranceFromNextRoomX() {
  return entranceFromNextRoomX;
}


int Room::getEntranceFromNextRoomY() {
  return entranceFromNextRoomY;
}


int Room::getEntranceFromPrevRoomX() {
  return entranceFromPrevRoomX;
}


int Room::getEntranceFromPrevRoomY() {
  return entranceFromPrevRoomY;
}


int Room::getExitToNextRoomX() {
  return exitToNextRoomX;
}


int Room::getExitToNextRoomY() {
  return exitToNextRoomY;
}


int Room::getExitToPrevRoomX() {
  return exitToPrevRoomX;
}


int Room::getExitToPrevRoomY() {
  return exitToPrevRoomY;
}


void Room::setEntranceFromNextRoomX(int newX) {
  entranceFromNextRoomX = newX;

}


void Room::setEntranceFromNextRoomY(int newY) {
  entranceFromNextRoomY = newY;

}


void Room::setEntranceFromPrevRoomX(int newX) {
  entranceFromPrevRoomX = newX;

}


void Room::setEntranceFromPrevRoomY(int newY) {
  entranceFromPrevRoomY = newY;

}


void Room::setExitToNextRoomX(int newX) {
  exitToNextRoomX = newX;

}


void Room::setExitToNextRoomY(int newY) {
  exitToNextRoomY = newY;

}


void Room::setExitToPrevRoomX(int newX) {
  exitToPrevRoomX = newX;

}


void Room::setExitToPrevRoomY(int newY) {
  exitToPrevRoomY = newY;

}

