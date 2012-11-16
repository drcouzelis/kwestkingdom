#include <stdio.h>

#include "character.h"
#include "colors.h"
#include "direction.h"
#include "game.h"
#include "level.h"
#include "memory.h"
#include "player.h"
#include "resources.h"
#include "room.h"
#include "screen.h"
#include "sprite.h"
#include "world.h"




/**
 * Private
 */




#define PLAYER_START_ROW (ROWS - 3)
#define PLAYER_START_COL (COLS / 2)




SNAPSHOT *create_snapshot()
{
  SNAPSHOT *shot;
  
  shot = alloc_memory("SNAPSHOT", sizeof(SNAPSHOT));
  
  shot->film = create_bitmap(grab_canvas_width(), grab_canvas_height());
  
  shot->sprite = create_sprite();
  
  return shot;
}




void destroy_snapshot(SNAPSHOT *shot)
{
  if (shot == NULL) {
    return;
  }
  
  destroy_bitmap(shot->film);
  destroy_sprite(shot->sprite);
  
  free_memory("SNAPSHOT", shot);
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




void transition_to_new_room(WORLD *world, int dir)
{
  SPRITE *prev;
  SPRITE *next;
  
  prev = world->prev_snapshot->sprite;
  next = world->next_snapshot->sprite;
  
  /**
   * Prepare the room transition.
   */
  if (dir == EAST) {
    warp_sprite(prev, 0, 0);
    move_sprite(prev, 0, COLS);
    prev->speed = grab_canvas_width();
    warp_sprite(next, 0, -COLS);
    move_sprite(next, 0, 0);
    next->speed = grab_canvas_width();
  } else if (dir == WEST) {
    warp_sprite(prev, 0, 0);
    move_sprite(prev, 0, -COLS);
    prev->speed = grab_canvas_width();
    warp_sprite(next, 0, COLS);
    move_sprite(next, 0, 0);
    next->speed = grab_canvas_width();
  } else if (dir == SOUTH) {
    warp_sprite(prev, 0, 0);
    move_sprite(prev, ROWS, 0);
    prev->speed = grab_canvas_height();
    warp_sprite(next, -ROWS, 0);
    move_sprite(next, 0, 0);
    next->speed = grab_canvas_height();
  } else if (dir == NORTH) {
    warp_sprite(prev, 0, 0);
    move_sprite(prev, -ROWS, 0);
    prev->speed = grab_canvas_height();
    warp_sprite(next, ROWS, 0);
    move_sprite(next, 0, 0);
    next->speed = grab_canvas_height();
  } else {
    warp_sprite(prev, 0, 0);
    warp_sprite(next, 0, 0);
  }
  
  world->state = WORLD_SCROLLING_STATE;
}




void play_in_world(WORLD *world)
{
  world->state = WORLD_NORMAL_STATE;
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
  paint_room(grab_room(world), world->prev_snapshot->film);
  
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
  paint_room(grab_room(world), world->next_snapshot->film);
  paint_sprite(world->player->character->sprite, world->next_snapshot->film);
  
  /**
   * Make the world scroll to the next room.
   */
  transition_to_new_room(world, calc_edge_dir(entr_row, entr_col));
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
  
  world->prev_snapshot = create_snapshot();
  world->next_snapshot = create_snapshot();
  
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
  
  destroy_snapshot(world->prev_snapshot);
  destroy_snapshot(world->next_snapshot);

  free_memory("WORLD", world);
}




void update_world(WORLD *world)
{
  SPRITE *sprite;
  DOOR *door;
  
  switch (world->state) {
  
  case WORLD_NORMAL_STATE:
    
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
    
    break;
    
  case WORLD_SCROLLING_STATE:
    update_sprite(world->prev_snapshot->sprite);
    update_sprite(world->next_snapshot->sprite);
    if (!is_moving(world->next_snapshot->sprite)) {
      play_in_world(world);
    }
    break;
  }
}




void paint_world(WORLD *world, BITMAP *canvas)
{
  char room_num_text[16];
  
  switch (world->state) {
  
  case WORLD_NORMAL_STATE:
    paint_room(grab_room(world), canvas);
    paint_sprite(world->player->character->sprite, canvas);
    break;
    
  case WORLD_SCROLLING_STATE:
    blit(world->prev_snapshot->film, canvas, 0, 0, world->prev_snapshot->sprite->x, world->prev_snapshot->sprite->y, grab_canvas_width(), grab_canvas_height());
    blit(world->next_snapshot->film, canvas, 0, 0, world->next_snapshot->sprite->x, world->next_snapshot->sprite->y, grab_canvas_width(), grab_canvas_height());
    break;
  }
  
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
