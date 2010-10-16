#include "character.h"
#include "kwestkingdom.h"
#include "memory.h"
#include "player.h"
#include "room.h"
#include "sprite.h"
#include "world.h"




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

  world->num_rooms = 0;
  world->room_idx = 0;
  
  world->num_cached_rooms = 0;
  world->max_cached_rooms = 0;
  
  /**
   * Initialize function pointers
   */
  world->create_room = NULL;
  world->is_game_won = NULL;

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




void remove_oldest_room(WORLD *world)
{
  int oldest_idx = -1;
  int i;
  
  for (i = 0; i < MAX_ROOMS; i++) {
    if (world->rooms[i] != NULL) {
      if (oldest_idx == -1 || world->rooms[i]->num < world->rooms[oldest_idx]->num) {
        oldest_idx = i;
      }
    }
  }
  
  if (oldest_idx != -1) {
    destroy_room(world->rooms[oldest_idx]);
    world->rooms[oldest_idx] = NULL;
    world->num_rooms--;
  }
}




void add_room(WORLD *world, ROOM *room)
{
  if (world == NULL || room == NULL) {
    return;
  }
  
  world->rooms[world->num_rooms] = room;
  world->num_rooms++;
  
  if (world->num_rooms > world->max_cached_rooms) {
    remove_oldest_room(world);
  }
}




struct ROOM *current_room(WORLD *world)
{
  return world->rooms[world->room_idx];
}




int find_highest_room_number(WORLD *world)
{
  int highest = 0;
  int i;
  
  for (i = 0; i < MAX_ROOMS; i++) {
    if (world->rooms[i] != NULL && world->rooms[i]->num > highest) {
      highest = world->rooms[i]->num;
    }
  }
  
  return highest;
}




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




void update_world(WORLD *world)
{
  PLAYER *player;
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
  player = world->player;
  
  if (!is_moving(player->character->sprite)) {
    
    door = find_door(current_room(world), player->character->sprite->row, player->character->sprite->col);
    
    if (door != NULL) {
      printf("Standing on door %d %d, to %d at %d %d \n", door->row, door->col, door->new_room_num, door->new_row, door->new_col);
    }
  }
}




void paint_world(WORLD *world, BITMAP *canvas)
{
  paint_room(world->rooms[world->room_idx], canvas);
  paint_sprite(world->player->character->sprite, canvas);
}
