#include "character.h"
#include "colors.h"
#include "memory.h"
#include "player.h"
#include "resources.h"
#include "room.h"
#include "sprite.h"
#include "world.h"




/**
 * Private
 */




#define PLAYER_START_ROW (ROWS - 3)
#define PLAYER_START_COL (COLS / 2)




void sort_rooms(WORLD *world)
{
  ROOM *room;
  int i;
  int j;
  FLAG done;
  
  for (i = 1; i < MAX_ROOMS; i++) {
    
    room = world->rooms[i];
    j = i - 1;
    done = OFF;
    
    while (!done) {
      
      if (
        (world->rooms[j] == NULL && room != NULL) ||
        (room != NULL && world->rooms[j]->num > room->num)
      ) {
        
        world->rooms[j + 1] = world->rooms[j];
        j--;
        
        if (j < 0) {
          done = ON;
        }
        
      } else {
        
        done = ON;
      }
    }
    
    world->rooms[j + 1] = room;
  }
}




void remove_oldest_room(WORLD *world)
{
  destroy_room(world->rooms[0]);
  world->rooms[0] = NULL;
  
  sort_rooms(world);
}




int count_num_rooms(WORLD *world)
{
  int count = 0;
  int i;
  
  for (i = 0; i < MAX_ROOMS; i++) {
    if (world->rooms[i] != NULL) {
      count++;
    }
  }
  
  return count;
}




int find_highest_room_number(WORLD *world)
{
  return world->rooms[count_num_rooms(world) - 1]->num;
}




/**
 * See if the last character is done taking their turn.
 * Find out whose turn it is next.
 * Tell them to take a turn.
 */
void update_turn(WORLD *world)
{
  /*int index;*/
  
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
  if (is_waiting(world->player->character)) {
    take_turn(world->player->character);
  }
}




/**
 * Find the door that corresponds to the given row and col.
 */
DOOR *find_door(ROOM *room, int row, int col)
{
  int i;
  
  for (i = 0; i < MAX_DOORS; i++) {
    if (room->doors[i] != NULL && room->doors[i]->row == row && room->doors[i]->col == col) {
      return room->doors[i];
    }
  }
  
  return NULL;
}




void change_room(WORLD *world, int new_room_num)
{
  int i;
  
  /**
   * Continue caching rooms until
   * the right room number is found.
   */
  while (ON) {
    
    for (i = 0; i < MAX_ROOMS; i++) {
      if (world->rooms[i] != NULL && world->rooms[i]->num == new_room_num) {
        world->room_idx = i;
        return;
      }
    }
    
    cache_rooms(world);
  }
}




/**
 * Used when walking through a door.
 */
void use_door(WORLD *world, DOOR *door)
{
  change_room(world, door->new_room_num);
  warp_sprite(world->player->character->sprite, door->new_row, door->new_col);
}




/**
 * Public
 */




WORLD *create_world()
{
  WORLD *world;
  int i;

  world = alloc_memory(sizeof(WORLD));

  world->player = create_player();
  warp_sprite(world->player->character->sprite, PLAYER_START_ROW, PLAYER_START_COL);

  for (i = 0; i < MAX_ROOMS; i++) {
    world->rooms[i] = NULL;
  }

  world->room_idx = 0;
  
  world->num_cached_rooms = 0;
  world->max_cached_rooms = 0;
  
  /**
   * Initialize function pointers
   */
  world->create_room = NULL;
  world->is_end_of_world = NULL;

  return world;
}




void destroy_world(WORLD *world)
{
  int i;
  
  if (world == NULL) {
    return;
  }

  destroy_player(world->player);
  
  /**
   * Destroy all rooms
   */
  for (i = 0; i < MAX_ROOMS; i++) {
    destroy_room(world->rooms[i]);
  }

  free_memory(world);
}




void add_room(WORLD *world, ROOM *room)
{
  int num_rooms;
  
  num_rooms = count_num_rooms(world);
  
  if (num_rooms < MAX_ROOMS) {
    world->rooms[num_rooms] = room;
    sort_rooms(world);
  }
  
  num_rooms++;
  
  if (num_rooms > world->max_cached_rooms) {
    remove_oldest_room(world);
  }
}




struct ROOM *grab_room(WORLD *world)
{
  return world->rooms[world->room_idx];
}




void cache_rooms(WORLD *world)
{
  ROOM *room;
  int i;
  
  for (i = 0; i < world->num_cached_rooms; i++) {
    room = world->create_room(world, find_highest_room_number(world) + 1);
    add_room(world, room);
  }
}




void update_world(WORLD *world)
{
  SPRITE *sprite;
  DOOR *door;
  
  update_turn(world);
  update_player(world->player, world);
  update_room(world->rooms[world->room_idx]);
  
  /**
   * If using door
   *   Draw current room to canvas
   *   If next room doesn't exist
   *     Create a new set of cached rooms (amount is num_cached_rooms)
   *     When adding a room, check max_cached_rooms and delete as needed
   *     For every door-reference to the deleted room, mark the door as a wall
   *   Move to the next room
   */
  sprite = world->player->character->sprite;
  
  if (!is_moving(sprite)) {
    
    door = find_door(grab_room(world), sprite->row, sprite->col);
    
    if (door != NULL) {
      use_door(world, door);
    }
  }
}




void paint_world(WORLD *world, BITMAP *canvas)
{
  char room_num_text[16];
  
  paint_room(world->rooms[world->room_idx], canvas);
  paint_sprite(world->player->character->sprite, canvas);
  
  /**
   * Show the current room number
   */
  sprintf(room_num_text, "Room %d", grab_room(world)->num);
  
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
