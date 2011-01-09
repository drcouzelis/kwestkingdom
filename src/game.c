#include "anim.h"
#include "character.h"
#include "colors.h"
#include "engine.h"
#include "game.h"
#include "input.h"
#include "memory.h"
#include "player.h"
#include "resources.h"
#include "room.h"
#include "room_gen.h"
#include "screen.h"
#include "sound.h"
#include "world.h"
#include "world_gen.h"
#include "kwestkingdom.h"




/**
 * Private
 */




enum
{
  GAME_PLAY_STATE,
  GAME_OVER_STATE
  /*GAME_QUIT_STATE,*/
  /*GAME_ENTER_INITIALS_STATE*/
};




void change_game_state(GAME *game, int state)
{
  game->state = state;

  switch (state) {

  /*
  case GAME_ENTER_INITIALS_STATE:
    clear_keybuf();
    // Disable the fullscreen and sound keys so the player could enter initials.
    [fullscreenKey free];
    fullscreenKey = nil;
    [soundKey free];
    soundKey = nil;
    break;
  */

  }
}




GAME *create_game()
{
  GAME *game;

  game = alloc_memory(sizeof(GAME));

  game->world = NULL;
  
  /**
   * Load the game over image
   */
  game->gameover_anim = create_anim(0, OFF);
  add_frame(game->gameover_anim, grab_image(IMG_GAMEOVER, NORMAL));
  
  /**
   * Load images for the user interface
   */
  game->full_heart_anim = create_anim(0, OFF);
  add_frame(game->full_heart_anim, grab_image(IMG_ITEMS_HEART, NORMAL));
  
  game->empty_heart_anim = create_anim(0, OFF);
  add_frame(game->empty_heart_anim, grab_image(IMG_ITEMS_EMPTYHEART, NORMAL));
  
  change_game_state(game, GAME_PLAY_STATE);

  return game;
}




/**
 * Public
 */




GAME *create_story_game()
{
  GAME *game;
  
  game = create_game();
  game->world = create_story_world();
  
  return game;
}




GAME *create_endless_game()
{
  GAME *game;
  
  game = create_game();
  game->world = create_endless_world();
  
  return game;
}




void destroy_game(GAME *game)
{
  if (game == NULL) {
    return;
  }

  destroy_world(game->world);
  destroy_anim(game->gameover_anim);
  destroy_anim(game->full_heart_anim);
  destroy_anim(game->empty_heart_anim);

  free_memory(game);
}




FLAG is_game_over(GAME *game)
{
  if (game->world->player->character->health == 0) {
    return ON;
  }
  
  return OFF;
}




FLAG is_game_won(GAME *game)
{
  if (game->world->is_end_of_world == NULL) {
    return OFF;
  }
  
  return game->world->is_end_of_world(game->world);
}




void update_game(GAME *game, ENGINE *engine)
{
  if (is_key_pressed(KEY_ESC)) {
    show_mainmenu(engine);
  }
  
  /*
  if (fullscreenKey != nil && [fullscreenKey isPressed]) {
    if (initializeScreen(-1, -1, is_windowed_mode()) == NO) {
      [self setState: GAME_QUIT_STATE];
    }
    setPalette();
  }

  if (soundKey != nil && [soundKey isPressed]) {
    toggleSound();
  }
  */

  switch (game->state) {

  case GAME_PLAY_STATE:
    /*
    if ([escapeKey isPressed]) {
      [self setState: GAME_MENU_STATE];
    }
    */
    update_world(game->world);
    
    if (is_game_over(game)) {
      change_game_state(game, GAME_OVER_STATE);
    }
    
    break;

  /*
  case GAME_ENTER_INITIALS_STATE:
    [self readPlayerInitials];
    if (strlen(playerInitials) > 0 && [selectKey isPressed]) {
      [self setState: GAME_MENU_STATE];
      [HighScoreLibrary addHighScoreWithInitials: playerInitials andRoom: [world getRoomNumber] andCoins: [world getMoney]];
      [world free];
      world = nil;
      strcpy(playerInitials, "\0");
    }
    break;

  case GAME_OVER_STATE:
    if ([selectKey isPressed]) {
      menuSelection = NEW_GAME_SELECTION;
      if ([HighScoreLibrary highScorePositionWithRoom: [world getRoomNumber] andCoins: [world getMoney]] == -1) {
        [self setState: GAME_MENU_STATE];
        [world free];
        world = nil;
      } else {
        [self setState: GAME_ENTER_INITIALS_STATE];
      }
    }
    break;

  case GAME_QUIT_STATE:
    // Do nothing.
    break;
  */

  }
}




void paint_game(GAME *game, BITMAP *canvas)
{
  int max_health;
  int health;
  int i;
  
  if (game == NULL || canvas == NULL) {
    return;
  }

  switch (game->state) {

  case GAME_PLAY_STATE:
    /* Paint the game */
    paint_world(game->world, canvas);
    
    /* Put the player's health on the screen. */
    max_health = game->world->player->character->max_health;
    health = game->world->player->character->health;
    
    for (i = 0; i < max_health; i++) {
      if (i < health) {
        paint_anim(game->full_heart_anim, canvas, grab_canvas_width() - (max_health + 1) * (grab_tile_size() / 2) + (i * (grab_tile_size() / 2)), 0);
      } else {
        paint_anim(game->empty_heart_anim, canvas, grab_canvas_width() - (max_health + 1) * (grab_tile_size() / 2) + (i * (grab_tile_size() / 2)), 0);
      }
    }
    
    break;
  }
}

