CC = gcc
OUTPUT = ../Linux/share/kwestkingdom/kwestkingdom
DEBUG = -Wall
LINKING_OPTIONS = -l objc
CFLAGS = $(shell allegro-config --cflags)
LDFLAGS = $(shell allegro-config --libs)

WIN_CC = wine c:\\MinGW\\bin\\gcc.exe
WIN_OUTPUT = ../Windows/kwestkingdom

HEADERS = al_screen.h Animation.h Archer.h Arrow.h Bow.h Character.h Chomper.h Collectable.h Drawable.h EndlessWorld.h Enemy.h ForestRoom.h Game.h Giant.h Hammer.h Heart.h HelpTile.h Hero.h HighScoreLibrary.h Inhabitable.h KeyControl.h KwestKingdom.h Livable.h Map.h Moneyable.h MoneyBag.h Ninja.h Positionable.h Resources.h RoomFactory.h Room.h Screen.h Shield.h Snapshot.h SnowRoom.h Sprite.h StoryWorld.h Sword.h Targetable.h Text.h Traversable.h UndergroundRoom.h Updatable.h World.h

OBJECTS = al_screen.o Animation.o Archer.o Arrow.o Bow.o Character.o Chomper.o EndlessWorld.o Enemy.o ForestRoom.o Game.o Giant.o Hammer.o Heart.o HelpTile.o Hero.o HighScoreLibrary.o KeyControl.o KwestKingdom.o Map.o MoneyBag.o Ninja.o Resources.o Room.o RoomFactory.o Screen.o Shield.o Snapshot.o SnowRoom.o Sprite.o StoryWorld.o Sword.o Text.o UndergroundRoom.o World.o

kwestkingdom: $(OBJECTS)
	 $(CC) $(DEBUG) $(LINKING_OPTIONS) -o $(OUTPUT) $(OBJECTS) $(LDFLAGS)

al_screen.o: al_screen.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c al_screen.cpp $(CFLAGS)

Animation.o: Animation.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Animation.cpp $(CFLAGS)

Archer.o: Archer.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Archer.cpp $(CFLAGS)

Arrow.o: Arrow.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Arrow.cpp $(CFLAGS)

Bow.o: Bow.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Bow.cpp $(CFLAGS)

Character.o: Character.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Character.cpp $(CFLAGS)

Chomper.o: Chomper.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Chomper.cpp $(CFLAGS)

EndlessWorld.o: EndlessWorld.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c EndlessWorld.cpp $(CFLAGS)

Enemy.o: Enemy.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Enemy.cpp $(CFLAGS)

ForestRoom.o: ForestRoom.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c ForestRoom.cpp $(CFLAGS)

Game.o: Game.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Game.cpp $(CFLAGS)

Giant.o: Giant.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Giant.cpp $(CFLAGS)

Hammer.o: Hammer.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Hammer.cpp $(CFLAGS)

Heart.o: Heart.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Heart.cpp $(CFLAGS)

HelpTile.o: HelpTile.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c HelpTile.cpp $(CFLAGS)

Hero.o: Hero.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Hero.cpp $(CFLAGS)

HighScoreLibrary.o: HighScoreLibrary.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c HighScoreLibrary.cpp $(CFLAGS)

KeyControl.o: KeyControl.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c KeyControl.cpp $(CFLAGS)

KwestKingdom.o: KwestKingdom.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c KwestKingdom.cpp $(CFLAGS)

Map.o: Map.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Map.cpp $(CFLAGS)

MoneyBag.o: MoneyBag.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c MoneyBag.cpp $(CFLAGS)

Ninja.o: Ninja.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Ninja.cpp $(CFLAGS)

Resources.o: Resources.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Resources.cpp $(CFLAGS)

Room.o: Room.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Room.cpp $(CFLAGS)

RoomFactory.o: RoomFactory.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c RoomFactory.cpp $(CFLAGS)

Screen.o: Screen.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Screen.cpp $(CFLAGS)

Shield.o: Shield.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Shield.cpp $(CFLAGS)

Snapshot.o: Snapshot.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Snapshot.cpp $(CFLAGS)

SnowRoom.o: SnowRoom.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c SnowRoom.cpp $(CFLAGS)

Sprite.o: Sprite.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Sprite.cpp $(CFLAGS)

StoryWorld.o: StoryWorld.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c StoryWorld.cpp $(CFLAGS)

Sword.o: Sword.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Sword.cpp $(CFLAGS)

Text.o: Text.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c Text.cpp $(CFLAGS)

UndergroundRoom.o: UndergroundRoom.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c UndergroundRoom.cpp $(CFLAGS)

World.o: World.cpp $(HEADERS)
	 $(CC) $(DEBUG) -c World.cpp $(CFLAGS)

clean:
	 rm -f $(OBJECTS)

win:
	 $(WIN_CC) $(DEBUG) *.cpp -o $(WIN_OUTPUT) -lobjc -lalleg

