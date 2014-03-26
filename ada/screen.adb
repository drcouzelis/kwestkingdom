with SDL.Events;
with SDL.Keyboard;
with SDL.Keysym;
with SDL.Quit;
with SDL.Types; use SDL.Types;
with SDL.Video;


package body Screen is

--
-- This puts an image on the screen at the specified location
--
procedure Blit_Bitmap(Bitmap, Surface : SDL.Video.Surface_Ptr; X : Sint16; Y : Sint16) is
  Dest : SDL.Video.Rect;
begin
  Dest.X := X;
  Dest.Y := Y;
  Dest.W := Uint16 (Bitmap.W);
  Dest.H := Uint16 (Bitmap.H);
  SDL.Video.BlitSurface (Bitmap, NULL, Surface, Dest);
end Blit_Bitmap;

  
end Screen;

