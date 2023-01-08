#include <math.h>
#include "util.h"

int32_t util::computeDistance(Pos p1, Pos p2) {
    return (int32_t)sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}