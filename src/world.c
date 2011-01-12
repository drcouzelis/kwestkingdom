#include "character.h"
#include "colors.h"
#include "memory.h"
#include "player.h"
#include "resources.h"
#include "room.h"
#include "sprite.h"
#include "world.h"
#include "world_gen.h"




#define PLAYER_START_ROW (ROWS - 3)
#define PLAYER_START_COL (COLS / 2)




FLAG world_exists = OFF;




/**
 * Represents the player, aka the hero!
 */
PLAYER *player = NULL;




/**
 * A list of rooms in this world.
 * Rooms will always be in order based on their number.
 */
ROOM *rooms[MAX_ROOMS];
int room_idx = 0;

/**
 * When it comes times to create a new set of rooms,
 * this many rooms will be created at a time.
 */
int num_cached_rooms = 10; /* Try 10 */




/**
 * When the max number of cached rooms is met,
 * one room will be deleted for every new cached
 * room that is created.
 * The max number of cached rooms must be equal
 * to or greater than the number of cached rooms.
 * (It doesn't make sense otherwise)
 */
int max_cached_rooms = 10; /* Try 10 */




/**
 * This function is used to create new rooms.
 * Different types of rooms need to be made for
 * different types of world.
 */
/*ROOM *(*create_room)(int num) = NULL;*/




/**
 * This function is used to see if the game
 * has been won.
 * Different types of worlds have different
 * win conditions.
 */
/*FLAG (*is_end_of_world)() = NULL;*/




void sort_rooms()
{
  ROOM *room;
  int i;
  int j;
  FLAG done;
  
  if (!world_exists) {
    return;
  }
  
  for (i = 1; i < MAX_ROOMS; i++) {
    
    room = rooms[i];
    j = i - 1;
    done = OFF;
    
    while (!done) {
      
      if (
        (rooms[j] == NULL && room != NULL) ||
        (room != NULL && rooms[j]->num > room->num)
      ) {
        
        rooms[j + 1] = rooms[j];
        j--;
        
        if (j < 0) {
          done = ON;
        }
        
      } else {
        
        done = ON;
      }
    }
    
    rooms[j + 1] = room;
  }
}




void remove_oldest_room()
{
  if (!world_exists) {
    return;
  }
  
  destroy_room(rooms[0]);
  rooms[0] = NULL;
  
  sort_rooms();
}




int count_num_rooms()
{
  int count = 0;
  int i;
  
  if (!world_exists) {
    return 0;
  }
  
  for (i = 0; i < MAX_ROOMS; i++) {
    if (rooms[i] != NULL) {
      count++;
    }
  }
  
  return count;
}




int find_highest_room_number()
{
  if (!world_exists) {
    return 0;
  }
  
  if (count_num_rooms() > 0) {
    return rooms[count_num_rooms() - 1]->num;
  }
  
  return 0;
}




/**
 * See if the last character is done taking their turn.
 * Find out whose turn it is next.
 * Tell them to take a turn.
 */
void update_turn()
{
  /*int index;*/
  
  if (!world_exists) {
    return;
  }
  
  /**
   * Determine whose turn it is next and tell them to go.
   */
  /*
  if (currentCharacter == nil || [currentCharacter waiting]) {
    
    if (currentCharacter == nil) {
      currentCharacter = hero;
    } else if (currentCharacter == hero) {
      currentCharacter = (Character *)[enemies getIndex: 0];
      if (currentCharacter == nil) {
        currentCharacter = hero;
      }
    } else {
      index = [enemies findIndex: currentCharacter];
      if (index >= 0) {
        currentCharacter = [enemies getIndex: index + 1];
      } else {
        currentCharacter = nil;
      }
      if (currentCharacter == nil) {
        currentCharacter = hero;
      }
    }
    
    [currentCharacter go];
  }
  */
  
  /* TEMP */
  if (is_waiting(player->character)) {
    take_turn(player->character);
  }
}




/**
 * Find the door that corresponds to the given row and col.
 */
DOOR *find_door(ROOM *room, int row, int col)
{
  int i;
  
  if (!world_exists) {
    return NULL;
  }
  
  for (i = 0; i < MAX_DOORS; i++) {
    if (room->doors[i] != NULL && room->doors[i]->row == row && room->doors[i]->col == col) {
      return room->doors[i];
    }
  }
  
  return NULL;
}




void change_room(int new_room_num)
{
  int i;
  
  if (!world_exists) {
    return;
  }
  
  /**
   * Continue caching rooms until
   * the right room number is found.
   */
  while (ON) {
    
    for (i = 0; i < MAX_ROOMS; i++) {
      if (rooms[i] != NULL && rooms[i]->num == new_room_num) {
        room_idx = i;
        return;
      }
    }
    
    cache_rooms();
  }
}




/**
 * Used when walking through a door.
 */
void use_door(DOOR *door)
{
  if (!world_exists) {
    return;
  }
  
  change_room(door->new_room_num);
  warp_sprite(player->character->sprite, door->new_row, door->new_col);
}




/**
 * Public
 */




void init_world()
{
  int i;

  if (world_exists) {
    stop_world();
  }
  
  player = create_player();
  warp_sprite(player->character->sprite, PLAYER_START_ROW, PLAYER_START_COL);

  for (i = 0; i < MAX_ROOMS; i++) {
    rooms[i] = NULL;
  }
  
  world_exists = ON;
}




void stop_world()
{
  int i;
  
  if (!world_exists) {
    return;
  }
  
  destroy_player(player);
  
  /**
   * Destroy all rooms
   */
  for (i = 0; i < MAX_ROOMS; i++) {
    destroy_room(rooms[i]);
  }
  
  world_exists = OFF;
}




PLAYER *grab_hot_player()
{
  return player;
}




void add_room(ROOM *room)
{
  int num_rooms;
  
  if (!world_exists) {
    return;
  }
  
  num_rooms = count_num_rooms();
  
  if (num_rooms < MAX_ROOMS) {
    rooms[num_rooms] = room;
    sort_rooms();
  }
  
  num_rooms++;
  
  if (num_rooms > max_cached_rooms) {
    remove_oldest_room();
  }
}




ROOM *grab_hot_room()
{
  if (!world_exists) {
    return NULL;
  }
  
  return rooms[room_idx];
}




void cache_rooms()
{
  ROOM *room;
  int i;
  
  if (!world_exists) {
    return;
  }
  
  for (i = 0; i < num_cached_rooms; i++) {
    room = create_story_world_room(find_highest_room_number() + 1);
    add_room(room);
  }
}




void update_world()
{
  SPRITE *sprite;
  DOOR *door;
  
  if (!world_exists) {
    return;
  }
  
  update_turn();
  update_player(player);
  update_room(rooms[room_idx]);
  
  /**
   * If using door
   *   Draw current room to canvas
   *   If next room doesn't exist
   *     Create a new set of cached rooms (amount is num_cached_rooms)
   *     When adding a room, check max_cached_rooms and delete as needed
   *     For every door-reference to the deleted room, mark the door as a wall
   *   Move to the next room
   */
  sprite = player->character->sprite;
  
  if (!is_moving(sprite)) {
    
    door = find_door(grab_hot_room(), sprite->row, sprite->col);
    
    if (door != NULL) {
      use_door(door);
    }
  }
}




void paint_world(BITMAP *canvas)
{
  char room_num_text[16];
  
  if (!world_exists) {
    return;
  }
  
  paint_room(rooms[room_idx], canvas);
  paint_sprite(player->character->sprite, canvas);
  
  /**
   * Show the current room number
   */
  sprintf(room_num_text, "Room %d", grab_hot_room()->num);
  
  textprintf_ex(
    canvas,
    font,
    canvas->w - (grab_tile_size() * 3) - (grab_tile_size() / 2), /* x */
    canvas->h - (grab_tile_size() / 2), /* y */
    WHITE,
    -1,
    room_num_text
  );
  
}
