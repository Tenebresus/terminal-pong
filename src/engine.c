#include "../include/engine.h"

void startAlternateScreen() {
    printf("\033[?1049h");
}

void endAlternateScreen() {
    printf("\33[?1049l");
}

void getScreenDimensions(int *dimensions) {

    char buffer[1024];
    FILE *fp;
    fp = popen("stty size", "r");
    fgets(buffer, sizeof(buffer), fp);

    int x = 0;
    int y = 0;

    int numberBuffer[3];
    int size = 0;

    int firstTime = 1;

    for (int i = 0; i < 7; i++) {

        if (buffer[i] != '\n' && buffer[i] != ' ') {
            numberBuffer[size] = buffer[i] - 48;
            size++;
        }

        if (buffer[i] == ' ' || buffer[i] == '\n') {
            if (firstTime) {
                y = calculateNumber(numberBuffer, size);
                firstTime = 0;
            } else {
                x = calculateNumber(numberBuffer, size);
            }

            numberBuffer[0] = '\0';
            size = 0;

        }
            
    }

    dimensions[0] = x;
    dimensions[1] = y;

}

void disableCanonMode() {

    struct termios original_termios, modified_termios;

    if (tcgetattr(STDIN_FILENO, &original_termios) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    modified_termios = original_termios;
    modified_termios.c_lflag &= ~(ICANON | ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &modified_termios) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

}

void nextGameTick() {

    fflush(stdout);
    usleep(33333);
    printf("\033c");

}

void initializeEngine() {

    srand(time(NULL));

    startAlternateScreen();
    disableCanonMode();

}

void deInitializeEngine() {

    disableCanonMode();
    endAlternateScreen();

}

int getPressedkey() {

    fd_set rfds;
    struct timeval tv;
    int retval;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    tv.tv_sec = 0;
    tv.tv_usec = 33333;

    retval = select(1, &rfds, NULL, NULL, &tv); 

    if (retval == -1) {
        perror("select()");
    } 

    else if (retval) {

        char pressedKeyBuffer[10];
        read(STDIN_FILENO, pressedKeyBuffer, 1);
        int pressedKey = pressedKeyBuffer[0];
        return pressedKey;

    }

    return 1;

}