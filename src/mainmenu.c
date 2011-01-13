#include "anim.h"
#include "colors.h"
#include "engine.h"
#include "game.h"
#include "input.h"
#include "kwestkingdom.h"
#include "mainmenu.h"
#include "memory.h"
#include "resources.h"
#include "room.h"
#include "room_gen.h"
#include "screen.h"
#include "sound.h"




enum
{
  MAINMENU_TITLE_STATE = 0,
  MAINMENU_HIGH_SCORES_STATE
};




enum {
  NEW_GAME_SELECTION = 0,
  SURVIVAL_MODE_SELECTION,
  RESUME_GAME_SELECTION,
  HIGH_SCORES_SELECTION,
  NUM_MENU_SELECTIONS
};




/**
 * The title screen image
 */
ANIM *title_anim = NULL;

/**
 * The selection icon
 */
ANIM *pointer_anim = NULL;

/**
 * The title screen background
 */
BITMAP *title_background = NULL;

/**
 * Which line the menu pointer is on
 */
int menu_selection = NEW_GAME_SELECTION;

/**
 * Intro, menu, or gameplay.
 */
int menu_state = MAINMENU_TITLE_STATE;




void paint_title_menu(BITMAP *canvas)
{
  int x;
  int y;
  int lineSpacing;
  int hTextOffset;
  int vTextOffset;
  int x_text_pos;
  int y_text_pos;

  x = (grab_canvas_width() / 2) - (grab_tile_size() * 4);
  y = (grab_canvas_height() / 2) - (grab_tile_size() / 2);
  lineSpacing = grab_tile_size() / 2;
  hTextOffset = grab_tile_size();
  vTextOffset = lineSpacing;

  blit(title_background, canvas, 0, 0, 0, 0, canvas->w, canvas->h);

  /**
   * Add a background "box" to the main menu.
   */
  rectfill(
    canvas,
    x,
    y,
    x + (grab_tile_size() * 4 * 2),
    y + (grab_tile_size() * 5),
    RED
  );

  /**
   * Paint the title of the game
   */
  paint_anim(
    title_anim,
    canvas,
    (grab_canvas_width() / 2) - (grab_anim_width(title_anim) / 2),
    (grab_canvas_width() - grab_anim_width(title_anim)) / 2
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
  if (can_resume_game()) {
    textout_ex(canvas, font, "Resume Game", x_text_pos, y_text_pos, WHITE, -1);
  } else {
    textout_ex(canvas, font, "Resume Game", x_text_pos, y_text_pos, GRAY, -1);
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
  paint_anim(pointer_anim, canvas, x - 4, y + vTextOffset + (lineSpacing * menu_selection) - 1);
  
  /* TEMP */
  /* Uncomment to see only the background image */
  /*blit(title_background, canvas, 0, 0, 0, 0, canvas->w, canvas->h);*/
}




void activate_mainmenu_selection()
{
  switch (menu_selection) {

  case NEW_GAME_SELECTION:
    menu_selection = RESUME_GAME_SELECTION;
    start_story_game();
    break;

  case SURVIVAL_MODE_SELECTION:
    menu_selection = RESUME_GAME_SELECTION;
    start_endless_game();
    break;

  case RESUME_GAME_SELECTION:
    resume_game();
    break;

  /*
  case HIGH_SCORES_SELECTION:
    [self setState: GAME_HIGH_SCORES_STATE];
    break;
  */
  }
}




void paint_random_room_image(int room_theme, BITMAP *canvas)
{
  ROOM *room;
  
  /*TERRAIN_OPTIONS terrain = {10, 90, 100, 0, OFF, OFF, WALL_PRIORITY};*/
  TERRAIN_OPTIONS terrain = {40, 0, 50, 0, OFF, OFF, WALL_PRIORITY};
  
  room = create_room();
  
  change_room_theme(room, room_theme);
  create_path(room, ROWS - 1, COLS / 2, 0, (COLS / 2) - 1);
  add_to_path(room, ROWS - 2, 1);
  generate_terrain(room, &terrain, OFF);
  
  paint_room(room, canvas);
  destroy_room(room);

}




/**
 * Public
 */




void init_mainmenu()
{
  /**
   * Load the game title
   */
  title_anim = create_anim(0, OFF);
  add_frame(title_anim, grab_image(IMG_TITLE, NORMAL));
  
  /**
   * Load the menu pointer
   */
  pointer_anim = create_anim(6, ON);
  add_frame(pointer_anim, grab_image(IMG_SWORD_HOLD_1, ROTATE));
  add_frame(pointer_anim, grab_image(IMG_SWORD_HOLD_2, ROTATE));
  add_frame(pointer_anim, grab_image(IMG_SWORD_HOLD_3, ROTATE));
  add_frame(pointer_anim, grab_image(IMG_SWORD_HOLD_4, ROTATE));

  /**
   * Used to draw the image behind the main menu
   */
  title_background = create_bitmap(grab_canvas_width(), grab_canvas_height());
}




void stop_mainmenu()
{
  destroy_anim(title_anim);
  destroy_anim(pointer_anim);
  destroy_bitmap(title_background);
}




void update_mainmenu()
{
  switch (menu_state) {
  
  case MAINMENU_TITLE_STATE:
    
    if (is_key_pressed(KEY_ESC)) {
      
      quit_kwestkingdom();
      
    } else if (is_key_pressed(KEY_UP)) {
      
      menu_selection--;
      
      if (menu_selection == RESUME_GAME_SELECTION && can_resume_game() == OFF) {
        menu_selection--;
      }
      
      if (menu_selection < 0) {
        menu_selection++;
      }
      
    } else if (is_key_pressed(KEY_DOWN)) {
      
      menu_selection++;
      
      if (menu_selection == RESUME_GAME_SELECTION && can_resume_game() == OFF) {
        menu_selection++;
      }
      
      if (menu_selection == NUM_MENU_SELECTIONS) {
        menu_selection--;
      }
      
    } else if (is_key_pressed(KEY_ENTER)) {
      
      activate_mainmenu_selection();
      
    }
    
    animate(pointer_anim);

    /**
     * Load the fullscreen and sound keys.
     * They were disabled so the player could enter initials.
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

  case MAINMENU_HIGH_SCORES_STATE:
    /*
    if ([escapeKey isPressed]) {
      [self setState: GAME_MENU_STATE];
    }
    */
    break;

  }
}




void paint_mainmenu(BITMAP *canvas)
{
  switch (menu_state) {

  case MAINMENU_TITLE_STATE:
    paint_title_menu(canvas);
    break;

  }
}




void generate_mainmenu_background()
{
  paint_random_room_image(ROOM_THEME_FOREST, title_background);
}

