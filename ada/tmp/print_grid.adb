with ada.text_io;
use ada.text_io;

procedure Print_Grid is
  
  Grid : array(1..16, 1..12) of Integer := (others => (others => 1));
  
begin
  
  for Y in Grid'range(2) loop
    for X in Grid'range(1) loop
      Grid(X, Y) := X;
      Put(Grid(X, Y)'img);
    end loop;
    New_Line;
  end loop;
  
  New_Line;
  
end Print_Grid;
