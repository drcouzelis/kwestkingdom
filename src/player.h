#ifndef PLAYER_HEADER
#define PLAYER_HEADER


/**
 * All of the different types of keys needed for input for
 * the player.
 */
enum
{
  /**
   * Movement
   */
  PLAYER_KEY_UP = 0,
  PLAYER_KEY_DOWN,
  PLAYER_KEY_LEFT,
  PLAYER_KEY_RIGHT,
  
  /**
   * Control
   */
  PLAYER_KEY_WAIT,
  PLAYER_KEY_USE,
  
  /**
   * Inventory shortcut
   */
  PLAYER_KEY_SHIELD,
  PLAYER_KEY_SWORD,
  PLAYER_KEY_BOW,
  
  NUM_PLAYER_KEYS
};


typedef struct PLAYER PLAYER;
struct CHARACTER;
struct WORLD;


struct PLAYER
{
  /**
   * Represents the player in the game.
   */
  struct CHARACTER *character;
  
  /**
   * The keys used to control the character.
   */
  char keys[NUM_PLAYER_KEYS];
};


PLAYER *create_player();
PLAYER *destroy_player(PLAYER *player);

void update_player(PLAYER *player, struct WORLD *world);


#endif
