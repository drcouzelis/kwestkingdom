CC = gcc
OUTPUT = ../Linux/share/kwestkingdom/kwestkingdom
DEBUG = -Wall
LINKING_OPTIONS = -l objc
CFLAGS = $(shell allegro-config --cflags)
LDFLAGS = $(shell allegro-config --libs)

WIN_CC = wine c:\\MinGW\\bin\\gcc.exe
WIN_OUTPUT = ../Windows/kwestkingdom

HEADERS = al_screen.h Animation.h Archer.h Arrow.h Bow.h Character.h Chomper.h Collectable.h Drawable.h EndlessWorld.h Enemy.h ForestRoom.h Game.h Giant.h Hammer.h Heart.h HelpTile.h Hero.h HighScoreLibrary.h Inhabitable.h KeyControl.h KwestKingdom.h List.h Livable.h Map.h Moneyable.h MoneyBag.h Ninja.h Positionable.h ResourceLibrary.h Resources.h RoomFactory.h Room.h Screen.h Shield.h Snapshot.h SnowRoom.h Sprite.h StoryWorld.h Sword.h Targetable.h Text.h Traversable.h UndergroundRoom.h Updatable.h World.h

OBJECTS = al_screen.o Animation.o Archer.o Arrow.o Bow.o Character.o Chomper.o EndlessWorld.o Enemy.o ForestRoom.o Game.o Giant.o Hammer.o Heart.o HelpTile.o Hero.o HighScoreLibrary.o KeyControl.o KwestKingdom.o List.o Map.o MoneyBag.o Ninja.o ResourceLibrary.o RoomFactory.o Room.o Screen.o Shield.o Snapshot.o SnowRoom.o Sprite.o StoryWorld.o Sword.o Text.o UndergroundRoom.o World.o

kwestkingdom: $(OBJECTS)
	 $(CC) $(DEBUG) $(LINKING_OPTIONS) -o $(OUTPUT) $(OBJECTS) $(LDFLAGS)

al_screen.o: al_screen.m $(HEADERS)
	 $(CC) $(DEBUG) -c al_screen.m $(CFLAGS)

Animation.o: Animation.m $(HEADERS)
	 $(CC) $(DEBUG) -c Animation.m $(CFLAGS)

Archer.o: Archer.m $(HEADERS)
	 $(CC) $(DEBUG) -c Archer.m $(CFLAGS)

Arrow.o: Arrow.m $(HEADERS)
	 $(CC) $(DEBUG) -c Arrow.m $(CFLAGS)

Bow.o: Bow.m $(HEADERS)
	 $(CC) $(DEBUG) -c Bow.m $(CFLAGS)

Character.o: Character.m $(HEADERS)
	 $(CC) $(DEBUG) -c Character.m $(CFLAGS)

Chomper.o: Chomper.m $(HEADERS)
	 $(CC) $(DEBUG) -c Chomper.m $(CFLAGS)

EndlessWorld.o: EndlessWorld.m $(HEADERS)
	 $(CC) $(DEBUG) -c EndlessWorld.m $(CFLAGS)

Enemy.o: Enemy.m $(HEADERS)
	 $(CC) $(DEBUG) -c Enemy.m $(CFLAGS)

ForestRoom.o: ForestRoom.m $(HEADERS)
	 $(CC) $(DEBUG) -c ForestRoom.m $(CFLAGS)

Game.o: Game.m $(HEADERS)
	 $(CC) $(DEBUG) -c Game.m $(CFLAGS)

Giant.o: Giant.m $(HEADERS)
	 $(CC) $(DEBUG) -c Giant.m $(CFLAGS)

Hammer.o: Hammer.m $(HEADERS)
	 $(CC) $(DEBUG) -c Hammer.m $(CFLAGS)

Heart.o: Heart.m $(HEADERS)
	 $(CC) $(DEBUG) -c Heart.m $(CFLAGS)

HelpTile.o: HelpTile.m $(HEADERS)
	 $(CC) $(DEBUG) -c HelpTile.m $(CFLAGS)

Hero.o: Hero.m $(HEADERS)
	 $(CC) $(DEBUG) -c Hero.m $(CFLAGS)

HighScoreLibrary.o: HighScoreLibrary.m $(HEADERS)
	 $(CC) $(DEBUG) -c HighScoreLibrary.m $(CFLAGS)

KeyControl.o: KeyControl.m $(HEADERS)
	 $(CC) $(DEBUG) -c KeyControl.m $(CFLAGS)

KwestKingdom.o: KwestKingdom.m $(HEADERS)
	 $(CC) $(DEBUG) -c KwestKingdom.m $(CFLAGS)

List.o: List.m $(HEADERS)
	 $(CC) $(DEBUG) -c List.m $(CFLAGS)

Map.o: Map.m $(HEADERS)
	 $(CC) $(DEBUG) -c Map.m $(CFLAGS)

MoneyBag.o: MoneyBag.m $(HEADERS)
	 $(CC) $(DEBUG) -c MoneyBag.m $(CFLAGS)

Ninja.o: Ninja.m $(HEADERS)
	 $(CC) $(DEBUG) -c Ninja.m $(CFLAGS)

ResourceLibrary.o: ResourceLibrary.m $(HEADERS)
	 $(CC) $(DEBUG) -c ResourceLibrary.m $(CFLAGS)

RoomFactory.o: RoomFactory.m $(HEADERS)
	 $(CC) $(DEBUG) -c RoomFactory.m $(CFLAGS)

Room.o: Room.m $(HEADERS)
	 $(CC) $(DEBUG) -c Room.m $(CFLAGS)

Screen.o: Screen.m $(HEADERS)
	 $(CC) $(DEBUG) -c Screen.m $(CFLAGS)

Shield.o: Shield.m $(HEADERS)
	 $(CC) $(DEBUG) -c Shield.m $(CFLAGS)

Snapshot.o: Snapshot.m $(HEADERS)
	 $(CC) $(DEBUG) -c Snapshot.m $(CFLAGS)

SnowRoom.o: SnowRoom.m $(HEADERS)
	 $(CC) $(DEBUG) -c SnowRoom.m $(CFLAGS)

Sprite.o: Sprite.m $(HEADERS)
	 $(CC) $(DEBUG) -c Sprite.m $(CFLAGS)

StoryWorld.o: StoryWorld.m $(HEADERS)
	 $(CC) $(DEBUG) -c StoryWorld.m $(CFLAGS)

Sword.o: Sword.m $(HEADERS)
	 $(CC) $(DEBUG) -c Sword.m $(CFLAGS)

Text.o: Text.m $(HEADERS)
	 $(CC) $(DEBUG) -c Text.m $(CFLAGS)

UndergroundRoom.o: UndergroundRoom.m $(HEADERS)
	 $(CC) $(DEBUG) -c UndergroundRoom.m $(CFLAGS)

World.o: World.m $(HEADERS)
	 $(CC) $(DEBUG) -c World.m $(CFLAGS)

clean:
	 rm -f $(OBJECTS)

win:
	 $(WIN_CC) $(DEBUG) *.m -o $(WIN_OUTPUT) -lobjc -lalleg

