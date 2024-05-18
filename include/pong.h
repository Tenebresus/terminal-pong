#ifndef _PONG
#define _PONG

#include <stdio.h>
#include <math.h>

#endif

extern const int playerStep;

extern const int ballDirLeft;
extern const int ballDirRight;

struct Player {

    int x;
    int y;
    int score;

};

struct Ball {

    int x;
    int y;
    int direction;
    int velocityY;

};

void drawPlayer (struct Player *p);

void drawScreen (int x, int y, struct Player *pL, struct Player *pR);

void drawBall (struct Ball *b, struct Player *pL, struct Player *pR, int y);

int ballCollidedWithPlayerLeft (struct Ball *b, struct Player *pL);

int ballCollidedWithPlayerRight (struct Ball *b, struct Player *pR);

int ballCollidedWithBorder (struct Ball *b, int y);

void playerScored (struct Ball *b, struct Player *pL, struct Player *pR, int x, int y);