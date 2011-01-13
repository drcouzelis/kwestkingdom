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




FLAG game_running = OFF;




enum
{
  GAME_PLAY_STATE = 0,
  GAME_OVER_STATE
  /*GAME_QUIT_STATE,*/
  /*GAME_ENTER_INITIALS_STATE*/
};




/**
 * The game over image
 */
ANIM *gameover_anim = NULL;

/**
 * Player health icons
 */
ANIM *full_heart_anim = NULL;
ANIM *empty_heart_anim = NULL;

int game_state = GAME_PLAY_STATE;




void change_game_state(int state)
{
  game_state = state;

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




void init_game()
{
  init_world();
  
  /**
   * Load the game over image
   */
  if (gameover_anim == NULL) {
    gameover_anim = create_anim(0, OFF);
    add_frame(gameover_anim, grab_image(IMG_GAMEOVER, NORMAL));
  }
  
  /**
   * Load images for the user interface
   */
  if (full_heart_anim == NULL) {
    full_heart_anim = create_anim(0, OFF);
    add_frame(full_heart_anim, grab_image(IMG_ITEMS_HEART, NORMAL));
  }
  
  if (empty_heart_anim == NULL) {
    empty_heart_anim = create_anim(0, OFF);
    add_frame(empty_heart_anim, grab_image(IMG_ITEMS_EMPTYHEART, NORMAL));
  }
  
  change_game_state(GAME_PLAY_STATE);
  
  game_running = ON;
}




/**
 * Public
 */




void init_story_game()
{
  init_game();
  init_story_world();
}




void init_endless_game()
{
  init_game();
  init_endless_world();
}




void stop_game()
{
  stop_world();
  destroy_anim(gameover_anim);
  destroy_anim(full_heart_anim);
  destroy_anim(empty_heart_anim);
  
  game_running = OFF;
}




FLAG is_game_over()
{
  if (grab_hot_player()->character->health == 0) {
    return ON;
  }
  
  return OFF;
}




/*
FLAG is_game_won(GAME *game)
{
  if (game->world->is_end_of_world == NULL) {
    return OFF;
  }
  
  return game->world->is_end_of_world(game->world);
}
*/




void update_game()
{
  if (is_key_pressed(KEY_ESC)) {
    show_mainmenu();
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

  switch (game_state) {

  case GAME_PLAY_STATE:
    /*
    if ([escapeKey isPressed]) {
      [self setState: GAME_MENU_STATE];
    }
    */
    update_world();
    
    if (is_game_over()) {
      change_game_state(GAME_OVER_STATE);
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




void paint_game(BITMAP *canvas)
{
  int max_health;
  int health;
  int i;
  
  switch (game_state) {

  case GAME_PLAY_STATE:
    /* Paint the game */
    paint_world(canvas);
    
    /* Put the player's health on the screen. */
    max_health = grab_hot_player()->character->max_health;
    health = grab_hot_player()->character->health;
    
    for (i = 0; i < max_health; i++) {
      if (i < health) {
        paint_anim(full_heart_anim, canvas, grab_canvas_width() - (max_health + 1) * (grab_tile_size() / 2) + (i * (grab_tile_size() / 2)), 0);
      } else {
        paint_anim(empty_heart_anim, canvas, grab_canvas_width() - (max_health + 1) * (grab_tile_size() / 2) + (i * (grab_tile_size() / 2)), 0);
      }
    }
    
    break;
  }
}



FLAG can_resume_game()
{
  return game_running;
}

