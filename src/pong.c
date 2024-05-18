#include "../include/pong.h"

const int playerLength = 9;
const int playerCenter = playerLength - ((playerLength - 1) / 2);
const int playerStep = 1;

const int ballDirLeft = 0;
const int ballDirRight = 1;

void drawPlayer (struct Player *p) {

    for (int i = p->y; i < p->y + playerLength; i++) {

        printf("\033[%d;%dH", i, p->x);
        printf("||");

    }

}

void drawScreen (int x, int y, struct Player *pL, struct Player *pR) {

    for (int i = 0; i <= y; i++) {

        printf("\033[%d;%dH", i, x / 2);
        printf("|");

    }

    printf("\033[%d;%dH", 0, x / 4);
    printf("%d", pL->score);

    printf("\033[%d;%dH", 0, (x / 4) + (x / 2));
    printf("%d", pR->score);

}

void drawBall (struct Ball *b, struct Player *pL, struct Player *pR, int y) {

    printf("\033[%d;%dH", b->y, b->x);

    if (ballCollidedWithPlayerLeft(b, pL) || ballCollidedWithPlayerRight(b, pR)) {
        b->direction = !b->direction;
    }

    if (b->direction == ballDirLeft) {
        b->x--;
    }

    else if (b->direction == ballDirRight) {
        b->x++;
    }

    if (ballCollidedWithBorder(b, y)) {

        b->velocityY -= b->velocityY * 2;

    }

    b->y += b->velocityY;

}

int ballCollidedWithPlayerLeft (struct Ball *b, struct Player *pL) {
    if ((b->x == pL->x + 2) && (b->y >= pL->y && b->y <= pL->y + playerLength)) {
        int playerBodyPart = 1;
        for (int i = pL->y; i <= pL->y + playerLength; i++) {
            if (i == b->y) {     
                b->velocityY = playerBodyPart - playerCenter;
                break;
            }
            playerBodyPart++;
        }
        return 1;
    }
    return 0;
}

int ballCollidedWithPlayerRight (struct Ball *b, struct Player *pR) {
    if ((b->x == pR->x) && (b->y >= pR->y && b->y <= pR->y + playerLength)) {
        int playerBodyPart = 1;
            for (int i = pR->y; i <= pR->y + playerLength; i++) {
                if (i == b->y) {     
                    b->velocityY = playerBodyPart - playerCenter;
                    break;
                }
                playerBodyPart++;
            }
        return 1;
    }
    return 0;
}

int ballCollidedWithBorder (struct Ball *b, int y) {
    return (b->y <= 1) || (b->y >= y);
}

void playerScored (struct Ball *b, struct Player *pL, struct Player *pR, int x, int y) {

    if (b->x < 0) {
        pR->score++;
        b->x = x / 2;
        b->y = y / 2;
        b->velocityY = 0;
    }

    else if (b->x > x) {
        pL->score++;
        b->x = x / 2;
        b->y = y / 2;
        b->velocityY = 0;
    }

}