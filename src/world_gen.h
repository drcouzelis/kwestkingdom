#ifndef WORLD_GEN_HEADER
#define WORLD_GEN_HEADER


struct WORLD;
struct ROOM;


struct WORLD *create_story_world();
struct ROOM *create_story_world_room(struct WORLD *world, int num);

struct WORLD *create_endless_world();
struct ROOM *create_endless_world_room(struct WORLD *world, int num);


#endif
