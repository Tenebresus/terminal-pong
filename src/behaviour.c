#include "../include/behaviour.h"

void movePosition(int x, int y) {

    printf("\033[%d;%dH", y, x);

}