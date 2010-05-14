/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
#include "KwestKingdom.h"
#include "Game.h"
#include "Resources.h"
#include "Screen.h"


volatile int timer = 0;
volatile int fps_timer = 0;

Game* game;

//MIDI *bgm;


/**
 * To keep the game running at the correct frames per second
 */
void do_timer(void)
{
  timer++;
} END_OF_FUNCTION (do_timer);


/**
 * To display the current frames per second
 */
void game_time_ticker()
{
  fps_timer++;
}
END_OF_FUNCTION(game_time_ticker)


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


int random_number(int low, int high)
{
  return (rand() % (high - low + 1)) + low;
}


void init_game()
{
  allegro_init();
  
  install_timer();
  
  LOCK_VARIABLE(timer);
  LOCK_FUNCTION(do_timer);
  install_int_ex(do_timer, BPS_TO_TIMER(GAME_TICKER));
  
  LOCK_VARIABLE(fps_timer);
  LOCK_FUNCTION(game_time_ticker);
  install_int_ex(game_time_ticker, BPS_TO_TIMER(10));
  
  timer = 0;
  fps_timer = 0;
  
  srand(time(NULL));
  
  install_keyboard();
  
  init_resources();

  if (init_screen(WINDOW_WIDTH * DEFAULT_SCREEN_RATIO, WINDOW_HEIGHT * DEFAULT_SCREEN_RATIO, false) == false) {
    exit(0);
  }

  set_palette();
  set_window_size(WINDOW_WIDTH, WINDOW_HEIGHT);
  
  install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
  toggle_sound(); // Turn off sound
}


int main(int argc, char **argv)
{
  int timemark;
  int fps = 0;
  int frames_done = 0;
  int prevTime = 0;
  
  init_game();
  
  game = new Game();
  
  // Reset the timers just before the game begins.
  timer = 0;
  fps_timer = 0;
  
  while (game->continuePlaying()) {
    
    while (timer == 0) {
      rest(1);
    }
    
    while (timer > 0) {
      
      timemark = timer;
      
      game->update();
      
      timer--;
      
      if (timemark <= timer) {
        break;
      }
      
    }
    
    // If a second has passed since we last measured the frame rate...
    if (fps_timer - prevTime >= 10) {
      // fps now holds the the number of frames done in the last second.
      fps = frames_done;
      // Reset for the next second
      frames_done = 0;
      prevTime = fps_timer;
    }
    
    game->draw(get_window());
    //clear_to_color(getBuffer(), BLACK);
    textprintf_ex(get_window(), font, 10, 10, WHITE, -1, "FPS %d", fps);
    
    show_screen();
    
    frames_done++;
    
  }
  
  delete game;
  
  free_screen();
  
  free_resources();
  //destroy_midi(bgm);
  
  return 0;
}
END_OF_MAIN()
