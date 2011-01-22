CC = gcc
OUTPUT = ../share/kwestkingdom/kwestkingdom
DEBUG = -g -O2 -Wall -ansi -pedantic
LINKING_OPTIONS = 
CFLAGS = $(shell allegro-config --cflags)
LDFLAGS = $(shell allegro-config --libs)

HEADERS = al_screen.h anim.h character.h colors.h direction.h enemy.h engine.h equipment.h game.h input.h kwestkingdom.h level.h mainmenu.h memory.h messenger.h player.h resources.h room_gen.h room.h screen.h sound.h sprite.h timer.h utilities.h world.h

OBJECTS = al_screen.o anim.o character.o direction.o engine.o game.o input.o kwestkingdom.o level.o mainmenu.o memory.o player.o resources.o room.o room_gen.o screen.o sound.o sprite.o timer.o utilities.o world.o

kwestkingdom: $(OBJECTS)
	 mkdir -p ../share/kwestkingdom
	 $(CC) $(DEBUG) $(LINKING_OPTIONS) -o $(OUTPUT) $(OBJECTS) $(LDFLAGS)

al_screen.o: al_screen.c $(HEADERS)
	 $(CC) $(DEBUG) -c al_screen.c $(CFLAGS)

anim.o: anim.c $(HEADERS)
	 $(CC) $(DEBUG) -c anim.c $(CFLAGS)

character.o: character.c $(HEADERS)
	 $(CC) $(DEBUG) -c character.c $(CFLAGS)

direction.o: direction.c $(HEADERS)
	 $(CC) $(DEBUG) -c direction.c $(CFLAGS)

engine.o: engine.c $(HEADERS)
	 $(CC) $(DEBUG) -c engine.c $(CFLAGS)

game.o: game.c $(HEADERS)
	 $(CC) $(DEBUG) -c game.c $(CFLAGS)

input.o: input.c $(HEADERS)
	 $(CC) $(DEBUG) -c input.c $(CFLAGS)

kwestkingdom.o: kwestkingdom.c $(HEADERS)
	 $(CC) $(DEBUG) -c kwestkingdom.c $(CFLAGS)

level.o: level.c $(HEADERS)
	 $(CC) $(DEBUG) -c level.c $(CFLAGS)

mainmenu.o: mainmenu.c $(HEADERS)
	 $(CC) $(DEBUG) -c mainmenu.c $(CFLAGS)

memory.o: memory.c $(HEADERS)
	 $(CC) $(DEBUG) -c memory.c $(CFLAGS)

player.o: player.c $(HEADERS)
	 $(CC) $(DEBUG) -c player.c $(CFLAGS)

resources.o: resources.c $(HEADERS)
	 $(CC) $(DEBUG) -c resources.c $(CFLAGS)

room.o: room.c $(HEADERS)
	 $(CC) $(DEBUG) -c room.c $(CFLAGS)

room_gen.o: room_gen.c $(HEADERS)
	 $(CC) $(DEBUG) -c room_gen.c $(CFLAGS)

screen.o: screen.c $(HEADERS)
	 $(CC) $(DEBUG) -c screen.c $(CFLAGS)

sound.o: sound.c $(HEADERS)
	 $(CC) $(DEBUG) -c sound.c $(CFLAGS)

sprite.o: sprite.c $(HEADERS)
	 $(CC) $(DEBUG) -c sprite.c $(CFLAGS)

timer.o: timer.c $(HEADERS)
	 $(CC) $(DEBUG) -c timer.c $(CFLAGS)

utilities.o: utilities.c $(HEADERS)
	 $(CC) $(DEBUG) -c utilities.c $(CFLAGS)

world.o: world.c $(HEADERS)
	 $(CC) $(DEBUG) -c world.c $(CFLAGS)

clean:
	 rm -f $(OBJECTS)

