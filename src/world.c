#include <stdio.h>

#include "character.h"
#include "colors.h"
#include "game.h"
#include "level.h"
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




void transition_to_new_room(WORLD *world, TRANSITION transition)
{
  if (transition == TRANS_SCROLL_N) {
  }
  
  
  world->state = WORLD_SCROLLING_STATE;
}




void play_in_world(WORLD *world)
{
  destroy_sprite(world->prev_snapshot);
  destroy_sprite(world->next_snapshot);
  
  world->state = WORLD_NORMAL_STATE;
}




SPRITE *take_snapshot(ROOM *room)
{
  return NULL;
}




/**
 * Used when walking through a door.
 */
void use_door(WORLD *world, DOOR *door)
{
  int entr_row;
  int entr_col;
  int next_num;
  TRANSITION transition;
  
  entr_row = door->new_row;
  entr_col = door->new_col;
  
  transition = door->transition;
  
  /**
   * Create a snapshot of the current room.
   */
  world->prev_snapshot = take_snapshot(grab_room(world));
  
  if (door->dest == NEXT_ROOM) {
    
    /**
     * Use the next room.
     */
    world->level->room_idx++;
    
  } else if (door->dest == PREV_ROOM) {
    
    /**
     * Use the previous room.
     */
    world->level->room_idx--;
    
  } else if (door->dest == NEXT_LEVEL) {
    
    /**
     * Create the next level.
     */
    next_num = world->level->num + 1;
    destroy_level(world->level);
    world->level = create_level(next_num, entr_row, entr_col);
  }
  
  /**
   * Now that we are using the new room,
   * put the player where he's supposed to be.
   */
  warp_sprite(world->player->character->sprite, entr_row, entr_col);
  
  /**
   * Take a snapshot of the new room.
   */
  world->next_snapshot = take_snapshot(grab_room(world));
  
  /**
   * Make the world scroll to the next room.
   */
  transition_to_new_room(world, transition);
}




int find_room_num(WORLD *world)
{
  int level_num;
  int room_num;
  
  /* The level number starts at 1 */
  level_num = world->level->num - 1;
  
  room_num = world->level->room_idx;
  
  return (level_num * ROOMS_PER_LEVEL) + room_num + 1;
}




/**
 * Public
 */




WORLD *create_world()
{
  WORLD *world;

  world = alloc_memory("WORLD", sizeof(WORLD));

  world->player = create_player();
  warp_sprite(world->player->character->sprite, PLAYER_START_ROW, PLAYER_START_COL);
  
  /**
   * Create the first level
   * with the path starting under the player.
   */
  world->level = create_level(1, PLAYER_START_ROW, PLAYER_START_COL);
  
  world->final_level = -1;
  
  world->prev_snapshot = NULL;
  world->next_snapshot = NULL;
  
  play_in_world(world);
  
  return world;
}




void destroy_world(WORLD *world)
{
  if (world == NULL) {
    return;
  }

  destroy_player(world->player);
  destroy_level(world->level);
  
  destroy_sprite(world->prev_snapshot);
  destroy_sprite(world->next_snapshot);

  free_memory("WORLD", world);
}




void update_world(WORLD *world)
{
  SPRITE *sprite;
  DOOR *door;
  
  update_turn(world);
  update_player(world->player, world);
  update_room(grab_room(world));
  
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
  
  paint_room(grab_room(world), canvas);
  paint_sprite(world->player->character->sprite, canvas);
  
  /**
   * Show the current room number
   */
  sprintf(room_num_text, "Room %d", find_room_num(world));
  
  show_text(
    canvas,
    room_num_text,
    canvas->w - (grab_tile_size() * 3) - (grab_tile_size() / 2), /* x */
    canvas->h - (grab_tile_size() / 2), /* y */
    WHITE,
    BLACK
  );
}




ROOM *grab_room(WORLD *world)
{
  return world->level->rooms[world->level->room_idx];
}
