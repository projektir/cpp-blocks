#ifndef UTIL_HPP
#define UTIL_HPP

#include <utility>
#include <chrono>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 880;
const int SQUARE_SIZE = 40;

const int WIDTH = SCREEN_WIDTH / SQUARE_SIZE;
const int HEIGHT = SCREEN_HEIGHT / SQUARE_SIZE;

const std::chrono::milliseconds SPEED_INCREASE_INTERVAL(60000);
const std::chrono::milliseconds FALL_SPEED_INTERVAL_START(150);
const std::chrono::milliseconds INTERVAL_INCREASE(50);

const int FIGURE_PLACEMENT_CODE = 77;

enum Direction {DOWN, LEFT, RIGHT};

struct XY {
    int x = 0;
    int y = 0;
};

bool operator<(XY a, XY b);

#endif /* UTIL_HPP */
