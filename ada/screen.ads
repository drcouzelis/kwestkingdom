with Ada.Numerics.Discrete_Random;
with Ada.Text_IO;
with Interfaces.C.Strings;
with SDL.Events;
with SDL.Keyboard;
with SDL.Keysym;
with SDL.Quit;
with SDL.Types; use SDL.Types;
with SDL.Video;


package Screen is
  
  ROWS : constant Integer := 12;
  COLS : constant Integer := 16;
  TILE_SIZE : constant Integer := 40;

  procedure Blit_Bitmap(Bitmap, Surface : SDL.Video.Surface_Ptr; X : Sint16; Y : Sint16);
  
end Screen;

