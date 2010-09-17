#include "anim.h"
#include "character.h"
#include "colors.h"
#include "game.h"
#include "player.h"
#include "resources.h"
#include "room.h"
#include "room_gen.h"
#include "screen.h"
#include "sound.h"
#include "world.h"
#include "kwestkingdom.h"




enum
{
  GAME_MENU_STATE = 0,
  GAME_PLAY_STATE,
  GAME_OVER_STATE
  /*GAME_HIGH_SCORES_STATE,*/
  /*GAME_QUIT_STATE,*/
  /*GAME_ENTER_INITIALS_STATE*/
};




enum {
  NEW_GAME_SELECTION = 0,
  SURVIVAL_MODE_SELECTION,
  RESUME_GAME_SELECTION,
  HIGH_SCORES_SELECTION,
  NUM_MENU_SELECTIONS
};




void change_game_state(GAME *game, int state);




GAME *create_game()
{
  GAME *game;
  ROOM *room;
  
  TERRAIN_OPTIONS terrain = {40, 0, 50, 0, OFF, OFF, WALL_PRIORITY};

  game = malloc(sizeof(GAME));

  game->world = create_world();

  /**
   * Initialize menu data
   */
  game->title_anim = create_anim(0, OFF);
  add_frame(game->title_anim, get_image(IMG_TITLE, NORMAL));

  game->gameover_anim = create_anim(0, OFF);
  add_frame(game->gameover_anim, get_image(IMG_GAMEOVER, NORMAL));

  game->pointer_anim = create_anim(6, ON);
  add_frame(game->pointer_anim, get_image(IMG_SWORD_HOLD_1, ROTATE));
  add_frame(game->pointer_anim, get_image(IMG_SWORD_HOLD_2, ROTATE));
  add_frame(game->pointer_anim, get_image(IMG_SWORD_HOLD_3, ROTATE));
  add_frame(game->pointer_anim, get_image(IMG_SWORD_HOLD_4, ROTATE));

  game->title_background = create_bitmap(canvas_width(), canvas_height());

  game->selection = 0;

  /**
   * Initialize game play data
   */
  room = create_room();
  set_room_theme(room, ROOM_THEME_FOREST);
  create_path(room, ROWS - 3, COLS / 2, 0, COLS / 2);
  generate_terrain(room, &terrain);
  
  add_room(game->world, room);
  
  /*change_game_state(game, GAME_MENU_STATE);*/
  change_game_state(game, GAME_PLAY_STATE); /* TEMP */

  return game;
}




void destroy_game(GAME *game)
{
  if (game == NULL) {
    return;
  }

  destroy_world(game->world);
  destroy_anim(game->title_anim);
  destroy_anim(game->gameover_anim);
  destroy_anim(game->pointer_anim);
  destroy_bitmap(game->title_background);

  free(game);
}




FLAG is_game_over(GAME *game)
{
  if (game && game->world && game->world->player->character->health == 0) {
    return ON;
  }
  
  return OFF;
}




FLAG is_game_won(GAME *game)
{
  if (game->world->type == ENDLESS_WORLD) {
    /* No end to endless */
    return OFF;
  }
  
  /* Check if the story has ended */
  return OFF; /* TEMP */
}




void update_game(GAME *game)
{
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

  case GAME_MENU_STATE:
    /*
    if ([escapeKey isPressed]) {
      [self setState: GAME_QUIT_STATE];
    } else if ([upKey isPressed]) {
      menuSelection--;
      if (menuSelection == RESUME_GAME_SELECTION && world == nil) {
        menuSelection--;
      }
      if (menuSelection < 0) {
        menuSelection++;
      }
    } else if ([downKey isPressed]) {
      menuSelection++;
      if (menuSelection == RESUME_GAME_SELECTION && world == nil) {
        menuSelection++;
      }
      if (menuSelection == MAX_MENU_SELECTIONS) {
        menuSelection--;
      }
    } else if ([selectKey isPressed]) {
      [self activateMenuSelection];
    }
    */
    animate(game->pointer_anim);
    break;

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
  case GAME_HIGH_SCORES_STATE:
    if ([escapeKey isPressed]) {
      [self setState: GAME_MENU_STATE];
    }
    break;

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




void paint_game_menu(GAME *game, BITMAP *canvas);




void paint_game(GAME *game, BITMAP *canvas)
{
  if (game == NULL || canvas == NULL) {
    return;
  }

  switch (game->state) {

  case GAME_MENU_STATE:
    paint_game_menu(game, canvas);
    break;

  case GAME_PLAY_STATE:
    /* Paint the game */
    paint_world(game->world, canvas);
    break;
  }
}




/**
 * Internal functions
 */




void paint_game_menu(GAME *game, BITMAP *canvas)
{
  int x;
  int y;
  int lineSpacing;
  int hTextOffset;
  int vTextOffset;
  int x_text_pos;
  int y_text_pos;

  x = (canvas_width() / 2) - (get_tile_size() * 4);
  y = (canvas_height() / 2) - (get_tile_size() / 2);
  lineSpacing = get_tile_size() / 2;
  hTextOffset = get_tile_size();
  vTextOffset = lineSpacing;

  blit(game->title_background, canvas, 0, 0, 0, 0, canvas->w, canvas->h);

  /**
   * Add a background "box" to the main menu.
   */
  rectfill(
    canvas,
    x,
    y,
    x + (get_tile_size() * 4 * 2),
    y + (get_tile_size() * 5),
    RED
  );

  /**
   * Paint the title of the game
   */
  paint_anim(
    game->title_anim,
    canvas,
    (canvas_width() / 2) - (anim_width(game->title_anim) / 2),
    (canvas_width() - anim_width(game->title_anim)) / 2
  );

  x_text_pos = x + hTextOffset;
  y_text_pos = y + vTextOffset;

  /* New Game */
  textout_ex(canvas, font, "New Game", x_text_pos, y_text_pos, WHITE, -1);

  /* Survival Mode */
  y_text_pos += lineSpacing;
  textout_ex(canvas, font, "Survival Mode", x_text_pos, y_text_pos, WHITE, -1);

  /* Resume Game */
  y_text_pos += lineSpacing;
  if (game->world == NULL) {
    textout_ex(canvas, font, "Resume Game", x_text_pos, y_text_pos, GRAY, -1);
  } else {
    textout_ex(canvas, font, "Resume Game", x_text_pos, y_text_pos, WHITE, -1);
  }

  /* High Scores */
  y_text_pos += lineSpacing;
  textout_ex(canvas, font, "High Scores", x_text_pos, y_text_pos, WHITE, -1);

  /* Quit */
  x_text_pos = x + hTextOffset - lineSpacing;
  y_text_pos += lineSpacing * 2;
  textout_ex(canvas, font, "Press ESC To Quit", x_text_pos, y_text_pos, WHITE, -1);

  /* Fullscreen */
  y_text_pos += lineSpacing;
  if (is_windowed_mode()) {
    textout_ex(canvas, font, "F for Fullscreen", x_text_pos, y_text_pos, WHITE, -1);
  } else {
    textout_ex(canvas, font, "F for Windowed", x_text_pos, y_text_pos, WHITE, -1);
  }

  /* Sound */
  y_text_pos += lineSpacing;
  if (is_sound_enabled()) {
    textout_ex(canvas, font, "S for Sound (On)", x_text_pos, y_text_pos, WHITE, -1);
  } else {
    textout_ex(canvas, font, "S for Sound (Off)", x_text_pos, y_text_pos, WHITE, -1);
  }

  /* The pointer to the current selection */
  paint_anim(game->pointer_anim, canvas, x - 4, y + vTextOffset + (lineSpacing * game->selection) - 1);
  
  /* TEMP */
  blit(game->title_background, canvas, 0, 0, 0, 0, canvas->w, canvas->h);
}




void activate_game_menu_selection(GAME *game)
{
  switch (game->selection) {

  case NEW_GAME_SELECTION:
    destroy_world(game->world);
    game->world = create_world();
    game->selection = RESUME_GAME_SELECTION;
    change_game_state(game, GAME_PLAY_STATE);
    break;

  case SURVIVAL_MODE_SELECTION:
    destroy_world(game->world);
    game->world = create_world();
    game->selection = RESUME_GAME_SELECTION;
    change_game_state(game, GAME_PLAY_STATE);
    break;

  /*
  case RESUME_GAME_SELECTION:
    if (world != nil) {
      [self setState: GAME_PLAY_STATE];
    }
    break;

  case HIGH_SCORES_SELECTION:
    [self setState: GAME_HIGH_SCORES_STATE];
    break;
  */
  }
}




void change_game_state(GAME *game, int state)
{
  ROOM *room;
  /*TERRAIN_OPTIONS terrain = {40, 0, 50, 0, OFF, OFF, WALL_PRIORITY};*/ /* Nice trees*/
  TERRAIN_OPTIONS terrain = {10, 90, 100, 0, OFF, OFF, WALL_PRIORITY};

  game->state = state;

  switch (state) {

  case GAME_MENU_STATE:
    room = create_room();
    set_room_theme(room, ROOM_THEME_FOREST);
    create_path(room, ROWS - 1, COLS / 2, 0, (COLS / 2) - 1);
    add_to_path(room, ROWS - 2, 1);
    generate_terrain(room, &terrain);
    paint_room(room, game->title_background);
    destroy_room(room);

    /**
     * Load the fullscreen and sound keys.
     * They are disabled so the player could enter initials.
     */
    /*
    if (fullscreenKey == nil) {
      fullscreenKey = [[KeyControl alloc] initWithKey: KEY_F];
      [fullscreenKey setDelay: GAME_TICKER];
    }
    if (soundKey == nil) {
      soundKey = [[KeyControl alloc] initWithKey: KEY_S];
      [soundKey setDelay: GAME_TICKER];
    }
    */
    break;

  /*
  case GAME_HIGH_SCORES_STATE:
    roomFactory = [[RoomFactory alloc] init];
    [roomFactory setType: ROOM_UNDERGROUND];
    [roomFactory setTerrain: ROOM_NO_WATER];
    tempRoom = [roomFactory createRoom];
    [tempRoom draw: [highScoresBackground getCanvas]];
    [tempRoom free];
    [roomFactory free];
    break;

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
