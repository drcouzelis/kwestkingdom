#import <Foundation/Foundation.h>


#define MAX_NUM_OF_HIGH_SCORES 5


typedef struct {
  char initials[4];
  int room;
  int coins;
} HighScore;


@interface HighScoreLibrary : NSObject {
}


+ initInstance;
+ (void) deallocInstance;
+ (int) highScorePositionWithRoom: (int) room andCoins: (int) coins;
+ addHighScoreWithInitials: (char *) initials andRoom: (int) room andCoins: (int) coins;
+ (BOOL) getHighScoreNumber: (int) num returnInitials: (char *) initials andRoom: (int *) room andCoins: (int *) coins;


@end
