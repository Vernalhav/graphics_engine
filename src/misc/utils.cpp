#include "utils.h"

float utils::randRange(float a, float b) {
    return (rand() / (float)RAND_MAX) * (b - a) + a;
}


int utils::randRangeInt(int a, int b) {
    return rand() % (b - a + 1) + a;
}