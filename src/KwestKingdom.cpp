#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "config.h"

#include "Game.h"
#include "KwestKingdom.h"
#include "resources.h"


ALLEGRO_DISPLAY *display = NULL;

Game *game;


int getTileSize()
{
  return TILE_SIZE;
}


int getWalkSpeed()
{
  return 60;
}


void game_over()
{
  game->gameOver();
}


int update_game(void *data)
{
  game->update();

  return game->continuePlaying();
}


void draw_game(void *data)
{
  al_set_target_bitmap(al_get_backbuffer(display));
  game->draw(NULL);
}


void run(int (*update)(void *data), void (*draw)(void *data), void *data)
{
  ALLEGRO_TIMER *timer = NULL;
  int keep_running = 1;
  int redraw = 1;

  ALLEGRO_EVENT_QUEUE *events = al_create_event_queue();
  ALLEGRO_EVENT event;

  timer = al_create_timer(1.0 / GAME_TICKER);
  al_register_event_source(events, al_get_timer_event_source(timer));

  al_start_timer(timer);

  while (keep_running) {

    al_wait_for_event(events, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {

      /* Update */
      keep_running = update(data);

      redraw = 1;
    }

    if (redraw && al_is_event_queue_empty(events)) {

      redraw = 0;

      /* Draw */
      draw(data);

      /* Update the screen */
      al_flip_display();
    }
  }

  al_destroy_event_queue(events);
  al_destroy_timer(timer);
}


void get_desktop_resolution(int adapter, int *w, int *h)
{
  /*
  ALLEGRO_MONITOR_INFO info;

  al_get_monitor_info(adapter, &info);

  *w = info.x2 - info.x1;
  *h = info.y2 - info.y1;
  */
  printf("Pretending to get the desktop resolution...\n");
  *w = 1680;
  *h = 1050;
}


int main(int argc, char **argv)
{
  /* For screen scaling */
  ALLEGRO_TRANSFORM trans;
  float scale_x = 1;
  float scale_y = 1;
  int scale = 1;
  int screen_w = 0;
  int screen_h = 0;

  int monitor_w = WINDOW_WIDTH;
  int monitor_h = WINDOW_HEIGHT;

  if (!al_init() || !al_init_image_addon() || !al_init_primitives_addon() || !al_install_keyboard() || !al_install_mouse()) {
    fprintf(stderr, "Failed to initialize allegro.\n");
    exit(1);
  }

  //al_init_font_addon();
  //al_init_ttf_addon();

  get_desktop_resolution(ALLEGRO_DEFAULT_DISPLAY_ADAPTER, &monitor_w, &monitor_h);

  /* Find the largest size the screen can be */
  scale_x = monitor_w / (float) WINDOW_WIDTH;
  scale_y = monitor_h / (float) WINDOW_HEIGHT;

  if (scale_x < scale_y) {
    scale = (int) scale_x;
  } else {
    scale = (int) scale_y;
  }

  /* TEMP */
  scale = 1;

  screen_w = scale * WINDOW_WIDTH;
  screen_h = scale * WINDOW_HEIGHT;

  /* Initialize the one and only global display for the game */
  display = al_create_display(screen_w, screen_h);

  if (!display) {
    fprintf(stderr, "Failed to create display.\n");
    exit(1);
  }

  /* Scale the screen to the largest size the monitor can handle */
  al_identity_transform(&trans);
  al_scale_transform(&trans, scale, scale);
  al_use_transform(&trans);

  /* Hide the mouse cursor */
  al_hide_mouse_cursor(display);

  toggle_sound(); // Turn off sound

  init_resources();
  add_resource_path( PKGDATADIR "/images/");
  add_resource_path( PKGDATADIR "/sounds/");

  /* Set the window title and icon */
  al_set_window_title(display, "Kwest Kingdom");
  //al_set_display_icon(display, IMG("icon.bmp")); // NEW_ALLEGRO

  game = new Game();

  /* START THE GAME */
  run(update_game, draw_game, NULL);

  // DONE, clean up
  delete game;
  stop_resources();
  al_destroy_display(display);
  
  return 0;
}

