#ifndef HIGHSCORELIBRARY_HEADER
#define HIGHSCORELIBRARY_HEADER


#define MAX_NUM_OF_HIGH_SCORES 5


typedef struct {
  char initials[4];
  int room;
  int coins;
} HighScore;


class HighScoreLibrary {

protected:

  HighScoreLibrary();
  ~HighScoreLibrary();

public:

  static void initInstance();
  static void deallocInstance();
  static int highScorePosition(int room, int coins);
  static void addHighScore(char *initials, int room, int coins);
  static bool getHighScore(int num, char *initials, int *room, int *coins);
};


#endif
