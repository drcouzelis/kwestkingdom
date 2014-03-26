with SDL.Types; use SDL.Types;
with SDL.Video;
with Screen;


package Terrain is
  
  Grass_Bitmap : SDL.Video.Surface_Ptr;
  Water_Bitmap : SDL.Video.Surface_Ptr;
  Mountain_Bitmap : SDL.Video.Surface_Ptr;
  Shore_North_Bitmap : SDL.Video.Surface_Ptr;
  Shore_South_Bitmap : SDL.Video.Surface_Ptr;
  Shore_East_Bitmap : SDL.Video.Surface_Ptr;
  Shore_West_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Inside_NE_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Inside_NW_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Inside_SE_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Inside_SW_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Outside_NE_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Outside_NW_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Outside_SE_Bitmap : SDL.Video.Surface_Ptr;
  Shore_Outside_SW_Bitmap : SDL.Video.Surface_Ptr;
  
  PATHWAY_OPEN : constant Integer := 0;
  PATHWAY_BLOCKED : constant Integer := 1;
  PATHWAY_PATH : constant Integer := 2;
  
  type Grid is Array(1..Screen.ROWS, 1..Screen.COLS) of Integer;
  
  procedure Create_Random_Pathway_Grid(H_Start, V_Start : Integer; Pathway_Grid: out Grid; H_Exit, V_Exit : out Integer);
  procedure Create_Random_Level_Grid(H_Start, V_Start : Integer; Level_Grid : out Grid; H_Exit, V_Exit : out Integer);
  procedure Add_Transparency(Bitmap_Ptr : SDL.Video.Surface_Ptr);
  procedure Initialize;
  procedure Quit;
  procedure Draw(Level_Grid : Grid; Surface : SDL.Video.Surface_Ptr);
  
end Terrain;

