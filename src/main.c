#include <stdio.h>

#include "../include/numbers.h"
#include "../include/engine.h"
#include "../include/behaviour.h"
#include "../include/pong.h"

int main() {

    initializeEngine();

    int dimensions[2];
    getScreenDimensions(dimensions);
    int x = dimensions[0];
    int y = dimensions[1];

    struct Player playerLeft;
    struct Player playerRight;

    playerLeft.x = 0;    
    playerLeft.y = y / 2;
    playerLeft.score = 0;

    playerRight.x = x - 1;
    playerRight.y = y / 2;
    playerRight.score = 0;

    struct Ball ball;
    ball.x = x / 2;
    ball.y = y / 2;
    ball.direction = ballDirLeft;
    ball.velocityY = 0;

    int gameOver = 0;

    while (!gameOver) {

        int keyPress = getPressedkey();

        switch(keyPress) {

            case 'w':
                playerLeft.y -= playerStep;
                break;

            case 's':
                playerLeft.y += playerStep;
                break;

            case 'i':
                playerRight.y -= playerStep;
                break;
            
            case 'k':
                playerRight.y += playerStep;
                break;
            
            default:
                break;

        }

        if (playerLeft.score == 5 || playerRight.score == 5) {
            gameOver = 1;
        }

        drawPlayer(&playerRight);
        drawPlayer(&playerLeft);
        drawScreen(x, y, &playerLeft, &playerRight);
        drawBall(&ball, &playerLeft, &playerRight, y);
        playerScored(&ball, &playerLeft, &playerRight, x, y);

        nextGameTick();

    }

    deInitializeEngine();

    return 0;
}
