#ifndef UTIL_HPP
#define UTIL_HPP

#include <utility>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 880;
const int SQUARE_SIZE = 40;

constexpr int WIDTH = SCREEN_WIDTH / SQUARE_SIZE;
constexpr int HEIGHT = SCREEN_HEIGHT / SQUARE_SIZE;

const int FIGURE_PLACEMENT_CODE = 77;

enum Direction {UP, DOWN, LEFT, RIGHT};

struct XY {
    int x = 0;
    int y = 0;
};

bool operator<(XY a, XY b);

#endif /* UTIL_HPP */
