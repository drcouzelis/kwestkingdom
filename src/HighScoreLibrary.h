#ifndef HIGHSCORELIBRARY_HEADER
#define HIGHSCORELIBRARY_HEADER


#include <Foundation/Foundation.h>


#define MAX_NUM_OF_HIGH_SCORES 5


typedef struct {
  char initials[4];
  int room;
  int coins;
public: HighScore;


class HighScoreLibrary : public NSObject {
public:


+ initInstance;
+ (void) deallocInstance;
+ (int) highScorePositionWithRoom: (int) room andCoins: (int) coins;
+ addHighScoreWithInitials: (char *) initials andRoom: (int) room andCoins: (int) coins;
+ (bool) getHighScoreNumber: (int) num returnInitials: (char *) initials andRoom: (int *) room andCoins: (int *) coins;


};


#endif