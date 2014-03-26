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
with Terrain;

procedure Quest_Of_Greatness is
  
  use type C.int;
  use type SDL.Init_Flags;
  use type SDL.Keysym.Key;
  
  Main_Surface : SDL.Video.Surface_Ptr;
  Event : SDL.Events.Event;
  PollEvent_Result : C.int;
  Quit : Boolean := False;
  
  Level_Grid : Terrain.Grid;
  Hero_Bitmap : SDL.Video.Surface_Ptr;
  
  H_Pos : Integer := Screen.COLS / 2;
  V_Pos : Integer := Screen.ROWS;
  Prev_H_Pos : Integer := 0;
  Prev_V_Pos : Integer := 0;
  
  H_Exit : Integer;
  V_Exit : Integer;
  
  Fullscreen : Boolean := False;
  
begin
  
  Ada.Text_IO.Put_Line("Welcome to the Quest of Greatness!");
  SDL.Init(SDL.INIT_TIMER or SDL.INIT_VIDEO);
  SDL.Quit.Atexit(SDL.SDL_Quit'Access);
  
  --
  -- Initialize the screen
  --
  Main_Surface := SDL.Video.SetVideoMode(Interfaces.C.int(Screen.COLS * Screen.TILE_SIZE), Interfaces.C.int(Screen.ROWS * Screen.TILE_SIZE), 16, SDL.Video.SWSURFACE);
  
  --
  -- Initialize a level
  --
  --Level_Grid := ((1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
                 --(1,1,1,1,1,0,0,0,0,0,2,2,2,2,2,2),
                 --(1,1,1,1,1,2,2,2,2,2,2,0,0,0,0,1),
                 --(1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,1),
                 --(2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1),
                 --(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1),
                 --(1,0,0,0,2,2,0,0,0,0,0,0,0,0,0,1),
                 --(1,0,0,2,2,2,2,0,0,0,0,0,0,0,0,1),
                 --(1,0,0,2,2,2,2,2,0,0,0,0,0,0,0,1),
                 --(1,0,0,2,2,2,2,2,0,0,0,0,0,0,0,1),
                 --(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1),
                 --(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1));
  
  Terrain.Initialize;
  Terrain.Create_Random_Level_Grid(H_Pos, V_Pos, Level_Grid, H_Exit, V_Exit);
  
  Hero_Bitmap := SDL.Video.LoadBmp(C.Strings.New_String("images/hero.bmp"));
  Terrain.Add_Transparency(Hero_Bitmap);
  
  --
  -- Begin the main game loop
  --
  while Quit = False loop
    
    --
    -- Check for keyboard input
    --
    SDL.Events.PollEventVP(PollEvent_Result, Event);
    if PollEvent_Result = 1 then
      case Event.The_Type is
        when SDL.Events.KEYDOWN =>
          -- Save the previous positions in case the sprite has to be put back
          Prev_H_Pos := H_Pos;
          Prev_V_Pos := V_Pos;
          if Event.Key.Keysym.Sym = SDL.Keysym.K_UP then
            V_Pos := V_Pos - 1;
          elsif Event.Key.Keysym.Sym = SDL.Keysym.K_DOWN then
            V_Pos := V_Pos + 1;
          elsif Event.Key.Keysym.Sym = SDL.Keysym.K_LEFT then
            H_Pos := H_Pos - 1;
          elsif Event.Key.Keysym.Sym = SDL.Keysym.K_RIGHT then
            H_Pos := H_Pos + 1;
          elsif Event.Key.Keysym.Sym = SDL.Keysym.K_ESCAPE then
            Quit := True;
          elsif Event.Key.Keysym.Sym = SDL.Keysym.K_F then
            SDL.Video.FreeSurface(Main_Surface);
            if Fullscreen then
              Main_Surface := SDL.Video.SetVideoMode(Interfaces.C.int(Screen.COLS * Screen.TILE_SIZE), Interfaces.C.int(Screen.ROWS * Screen.TILE_SIZE), 16, SDL.Video.SWSURFACE);
              Fullscreen := False;
            else
              Main_Surface := SDL.Video.SetVideoMode(Interfaces.C.int(Screen.COLS * Screen.TILE_SIZE), Interfaces.C.int(Screen.ROWS * Screen.TILE_SIZE), 16, SDL.Video.FULLSCREEN);
              Fullscreen := True;
            end if;
          end if;
          -- Bounds checking
          if H_Pos < 1 then
            H_Pos := 1;
          elsif H_Pos > Screen.COLS then
            H_Pos := Screen.COLS;
          end if;
          if V_Pos < 1 then
            V_Pos := 1;
          elsif V_Pos > Screen.ROWS then
            V_Pos := Screen.ROWS;
          end if;
          -- If the sprite tried to move onto an occupied tile
          -- then put him back where he was
          if Level_Grid(V_Pos, H_Pos) /= 0 then
            H_Pos := Prev_H_Pos;
            V_Pos := Prev_V_Pos;
          end if;
          -- If the sprite is at the exit then create the next level
          if H_Pos = H_Exit and V_Pos = V_Exit then
            if H_Pos = 1 then
              H_Pos := Screen.COLS;
            elsif H_Pos = Screen.COLS then
              H_Pos := 1;
            elsif V_Pos = 1 then
              V_Pos := Screen.ROWS;
            else
              V_Pos := 1;
            end if;
            Terrain.Create_Random_Level_Grid(H_Pos, V_Pos, Level_Grid, H_Exit, V_Exit);
          end if;
        when SDL.Events.QUIT => Quit := True;
        when others => null;
      end case;
    end if;
    
    --
    -- Update the graphics
    --
    Terrain.Draw(Level_Grid, Main_Surface);
    Screen.Blit_Bitmap(Hero_Bitmap, Main_Surface, Sint16((H_Pos - 1) * Screen.TILE_SIZE), Sint16((V_Pos - 1) * Screen.TILE_SIZE));
    SDL.Video.Flip(Main_Surface);
    
  end loop;
  
  --
  -- Clean up!
  --
  Terrain.Quit;
  SDL.Video.FreeSurface(Hero_Bitmap);
  SDL.Video.FreeSurface(Main_Surface);
  
end Quest_Of_Greatness;

