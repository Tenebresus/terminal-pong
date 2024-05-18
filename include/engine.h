#ifndef _ENGINE
#define _ENGINE

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "../include/numbers.h"

#endif

void startAlternateScreen();

void endAlternateScreen();

void getScreenDimensions(int *dimensions);

void disableCanonMode();

void nextGameTick();

int getPressedkey();

void initializeEngine();

void deInitializeEngine();