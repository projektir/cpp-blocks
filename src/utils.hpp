#ifndef UTIL_HPP
#define UTIL_HPP

#include <utility>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 880;
const int SQUARE_SIZE = 40;

const int FIGURE_PLACEMENT_CODE = 77;

enum Direction {UP, DOWN, LEFT, RIGHT};

struct XY {
    int x = 0;
    int y = 0;
};

bool operator<(XY a, XY b);

#endif /* UTIL_HPP */
