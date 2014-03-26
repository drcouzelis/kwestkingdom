with Ada.Numerics.Discrete_Random;
with Ada.Text_IO;
with Interfaces.C.Strings;
with SDL.Events;
with SDL.Keyboard;
with SDL.Keysym;
with SDL.Quit;
with SDL.Types; use SDL.Types;
with SDL.Video;
with Screen;


package body Terrain is


procedure Create_Random_Pathway_Grid(H_Start, V_Start : Integer; Pathway_Grid: out Grid; H_Exit, V_Exit : out Integer) is
  
  type Random_Small_Range is range 1..3;
  type Random_Large_Range is range -6..6;
  
  package Random_Small_Int is new Ada.Numerics.Discrete_Random(Random_Small_Range);
  package Random_Large_Int is new Ada.Numerics.Discrete_Random(Random_Large_Range);
  
  Small_Seed : Random_Small_Int.Generator;
  Large_Seed : Random_Large_Int.Generator;
  
  H_Path_Pos : Integer := H_Start;
  V_Path_Pos : Integer := V_Start;
  
  type Direction_Type is (NORTH, SOUTH, EAST, WEST);
  Direction : Direction_Type := NORTH;
  
  type Facing_Type is (STRAIGHT, TURN);
  Facing : Facing_Type := STRAIGHT;
  
  Num : Integer := 0;
  
begin
  
  Random_Small_Int.Reset(Small_Seed);
  Random_Large_Int.Reset(Large_Seed);
  
  --
  -- Clear the pathway grid
  --
  Pathway_Grid := (others => (others => PATHWAY_OPEN));
  
  --
  -- Mark the starting location as part of the path
  --
  Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
  
  if V_Path_Pos = Screen.ROWS then
    Direction := NORTH;
  elsif V_Path_Pos = 1 then
    Direction := SOUTH;
  elsif H_Path_Pos = 1 then
    Direction := EAST;
  elsif H_Path_Pos = Screen.COLS then
    Direction := WEST;
  end if;
  
  --
  -- Loop while not at the edge of the screen...
  --
  loop
    
    if Facing = STRAIGHT then
      Num := Integer(Random_Small_Int.Random(Small_Seed));
      if Direction = NORTH then
        for I in 1..Num loop
          V_Path_Pos := V_Path_Pos - 1;
          if V_Path_Pos < 1 then
            V_Path_Pos := 1;
          end if;
          Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
        end loop;
      elsif Direction = SOUTH then
        for I in 0..Num loop
          V_Path_Pos := V_Path_Pos + 1;
          if V_Path_Pos > Screen.ROWS then
            V_Path_Pos := Screen.ROWS;
          end if;
          Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
        end loop;
      elsif Direction = EAST then
        for I in 0..Num loop
          H_Path_Pos := H_Path_Pos + 1;
          if H_Path_Pos > Screen.COLS then
            H_Path_Pos := Screen.COLS;
          end if;
          Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
        end loop;
      elsif Direction = WEST then
        for I in 0..Num loop
          H_Path_Pos := H_Path_Pos - 1;
          if H_Path_Pos < 1 then
            H_Path_Pos := 1;
          end if;
          Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
        end loop;
      end if;
    end if;
    
    if Facing = TURN then
      Num := Integer(Random_Large_Int.Random(Large_Seed));
      if Direction = NORTH or Direction = SOUTH then
        if Num > 0 then
          for I in 1..Num loop
            H_Path_Pos := H_Path_Pos + 1;
            if H_Path_Pos > Screen.COLS then
              H_Path_Pos := Screen.COLS;
            end if;
            Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
          end loop;
        elsif Num < 0 then
          for I in 1..abs(Num) loop
            H_Path_Pos := H_Path_Pos - 1;
            if H_Path_Pos < 1 then
              H_Path_Pos := 1;
            end if;
            Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
          end loop;
        end if;
      elsif Direction = EAST or Direction = WEST then
        if Num > 0 then
          for I in 1..Num loop
            V_Path_Pos := V_Path_Pos + 1;
            if V_Path_Pos > Screen.ROWS then
              V_Path_Pos := Screen.ROWS;
            end if;
            Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
          end loop;
        elsif Num < 0 then
          for I in 1..abs(Num) loop
            V_Path_Pos := V_Path_Pos - 1;
            if V_Path_Pos < 1 then
              V_Path_Pos := 1;
            end if;
            Pathway_Grid(V_Path_Pos, H_Path_Pos) := PATHWAY_PATH;
          end loop;
        end if;
      end if;
    end if;
    
    if Facing = STRAIGHT then
      Facing := TURN;
    else
      Facing := STRAIGHT;
    end if;
    
    exit when H_Path_Pos = 1 or H_Path_Pos = Screen.COLS or V_Path_Pos = 1 or V_Path_Pos = Screen.ROWS;
  end loop;
  
  H_Exit := H_Path_Pos;
  V_Exit := V_Path_Pos;
  
  --
  -- Let's see what the newly created pathway looks like!
  --for ROW in Pathway_Grid'Range(1) loop
    --for COL in Pathway_Grid'Range(2) loop
      --Put(Pathway_Grid(ROW, COL)'Img);
    --end loop;
    --Put_Line("");
  --end loop;
  
end Create_Random_Pathway_Grid;


--
-- Generates a random level for the player to walk around in
--
procedure Create_Random_Level_Grid(H_Start, V_Start : Integer; Level_Grid : out Grid; H_Exit, V_Exit : out Integer) is
  
  type Random_Range is range 1..100;
  package Random_Int is new Ada.Numerics.Discrete_Random(Random_Range);
  Seed : Random_Int.Generator;
  Chance_Of_Water : Random_Range;
  Pathway_Grid : Grid;
  
begin
  
  Random_Int.Reset(Seed);
  
  Level_Grid := (others => (others => 0));
  
  Create_Random_Pathway_Grid(H_Start, V_Start, Pathway_Grid, H_Exit, V_Exit);
  
  for COL in Level_Grid'Range(2) loop
    for ROW in Level_Grid'Range(1) loop
      
      if Pathway_Grid(ROW, COL) /= PATHWAY_PATH then
        
        if COL = 1 or COL = Screen.COLS or ROW = 1 or ROW = Screen.ROWS then
          Level_Grid(ROW, COL) := 1; -- Mountain
        else
          
          --
          -- If this water is surrounded by water then increase its chance of being water
          --
          Chance_Of_Water := 3;
          if Level_Grid(ROW - 1, COL) = 2 or Level_Grid(ROW + 1, COL) = 2 or Level_Grid(ROW, COL - 1) = 2 or Level_Grid(ROW, COL + 1) = 2 then
            Chance_Of_Water := 50;
          end if;
          
          if Random_Int.Random(Seed) <= Chance_Of_Water then
            Level_Grid(ROW, COL) := 2; -- Water
          elsif Random_Int.Random(Seed) <= 10 then
            Level_Grid(ROW, COL) := 1; -- Mountain
          end if;
          
        end if;
        
      end if;
      
    end loop;
  end loop;
  
end Create_Random_Level_Grid;


procedure Add_Transparency(Bitmap_Ptr : SDL.Video.Surface_Ptr) is
begin
  --
  -- This makes the background color on the sprite transparent
  --
  SDL.Video.SetColorKey(Bitmap_Ptr, SDL.Video.SRCCOLORKEY, SDL.Video.MapRGB(Bitmap_Ptr.Format, 255, 0, 255));
end Add_Transparency;


procedure Initialize is
begin
  
  Grass_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/grass.bmp"));
  Water_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/water.bmp"));
  Mountain_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/mountain.bmp"));
  Shore_North_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_north.bmp"));
  Shore_South_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_south.bmp"));
  Shore_East_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_east.bmp"));
  Shore_West_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_west.bmp"));
  Shore_Inside_NE_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_inside_ne.bmp"));
  Shore_Inside_SE_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_inside_se.bmp"));
  Shore_Inside_NW_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_inside_nw.bmp"));
  Shore_Inside_SW_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_inside_sw.bmp"));
  Shore_Outside_NE_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_outside_ne.bmp"));
  Shore_Outside_SE_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_outside_se.bmp"));
  Shore_Outside_NW_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_outside_nw.bmp"));
  Shore_Outside_SW_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/shore_outside_sw.bmp"));
  
  Add_Transparency(Shore_North_Bitmap);
  Add_Transparency(Shore_South_Bitmap);
  Add_Transparency(Shore_East_Bitmap);
  Add_Transparency(Shore_West_Bitmap);
  Add_Transparency(Shore_Inside_NE_Bitmap);
  Add_Transparency(Shore_Inside_SE_Bitmap);
  Add_Transparency(Shore_Inside_NW_Bitmap);
  Add_Transparency(Shore_Inside_SW_Bitmap);
  Add_Transparency(Shore_Outside_NE_Bitmap);
  Add_Transparency(Shore_Outside_SE_Bitmap);
  Add_Transparency(Shore_Outside_NW_Bitmap);
  Add_Transparency(Shore_Outside_SW_Bitmap);
  
end Initialize;


procedure Quit is
begin
  SDL.Video.FreeSurface(Grass_Bitmap);
  SDL.Video.FreeSurface(Water_Bitmap);
  SDL.Video.FreeSurface(Mountain_Bitmap);
  SDL.Video.FreeSurface(Shore_North_Bitmap);
  SDL.Video.FreeSurface(Shore_South_Bitmap);
  SDL.Video.FreeSurface(Shore_East_Bitmap);
  SDL.Video.FreeSurface(Shore_West_Bitmap);
  SDL.Video.FreeSurface(Shore_Inside_NE_Bitmap);
  SDL.Video.FreeSurface(Shore_Inside_SE_Bitmap);
  SDL.Video.FreeSurface(Shore_Inside_NW_Bitmap);
  SDL.Video.FreeSurface(Shore_Inside_SW_Bitmap);
  SDL.Video.FreeSurface(Shore_Outside_NE_Bitmap);
  SDL.Video.FreeSurface(Shore_Outside_SE_Bitmap);
  SDL.Video.FreeSurface(Shore_Outside_NW_Bitmap);
  SDL.Video.FreeSurface(Shore_Outside_SW_Bitmap);
end Quit;


procedure Draw(Level_Grid : Grid; Surface : SDL.Video.Surface_Ptr) is
begin
  
  for Col in Level_Grid'Range(2) loop
    for Row in Level_Grid'Range(1) loop
      
      case Level_Grid(Row, Col) is
        when 0 => -- Grass
          Screen.Blit_Bitmap(Grass_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
        when 1 => -- Mountain
          Screen.Blit_Bitmap(Mountain_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
        when 2 => -- Water
          
          Screen.Blit_Bitmap(Water_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          
          --
          -- Add the shore
          --
          if Level_Grid(Row - 1, Col) /= 2 then -- North
            Screen.Blit_Bitmap(Shore_North_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row + 1, Col) /= 2 then -- South
            Screen.Blit_Bitmap(Shore_South_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row, Col + 1) /= 2 then -- East
            Screen.Blit_Bitmap(Shore_East_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row, Col - 1) /= 2 then -- West
            Screen.Blit_Bitmap(Shore_West_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          
          --
          -- Add the shore inside corners
          --
          if Level_Grid(Row - 1, Col) /= 2 and Level_Grid(Row, Col + 1) /= 2 then -- North East
            Screen.Blit_Bitmap(Shore_Inside_NE_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row + 1, Col) /= 2 and Level_Grid(Row, Col + 1) /= 2 then -- South East
            Screen.Blit_Bitmap(Shore_Inside_SE_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row - 1, Col) /= 2 and Level_Grid(Row, Col - 1) /= 2 then -- North West
            Screen.Blit_Bitmap(Shore_Inside_NW_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row + 1, Col) /= 2 and Level_Grid(Row, Col - 1) /= 2 then -- South West
            Screen.Blit_Bitmap(Shore_Inside_SW_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          
          --
          -- Add the shore outside corners
          --
          if Level_Grid(Row - 1, Col) = 2 and Level_Grid(Row, Col + 1) = 2 and Level_Grid(Row - 1, Col + 1) /= 2 then -- North East
            Screen.Blit_Bitmap(Shore_Outside_NE_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row + 1, Col) = 2 and Level_Grid(Row, Col + 1) = 2 and Level_Grid(Row + 1, Col + 1) /= 2 then -- South East
            Screen.Blit_Bitmap(Shore_Outside_SE_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row - 1, Col) = 2 and Level_Grid(Row, Col - 1) = 2 and Level_Grid(Row - 1, Col - 1) /= 2 then -- North West
            Screen.Blit_Bitmap(Shore_Outside_NW_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          if Level_Grid(Row + 1, Col) = 2 and Level_Grid(Row, Col - 1) = 2 and Level_Grid(Row + 1, Col - 1) /= 2 then -- South West
            Screen.Blit_Bitmap(Shore_Outside_SW_Bitmap, Surface, Sint16((Col - 1) * Screen.TILE_SIZE), Sint16((Row - 1) * Screen.TILE_SIZE));
          end if;
          
        when others => NULL;
      end case;
      
    end loop;
  end loop;
  
end Draw;


end Terrain;

