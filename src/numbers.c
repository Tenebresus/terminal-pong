#include "../include/numbers.h"

int calculateNumber (int *numbers, int size) {

    int sum = 0;
    int multiplier = pow(10, size) / 10;

    for (int i = 0; i < size; i++) {

        sum += numbers[i] * multiplier;
        multiplier = multiplier / 10;

    }

    return sum;

}