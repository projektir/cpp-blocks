#ifndef FIG_HPP
#define FIG_HPP

#include "SDL.h"
#include "SDL_image.h"
#include <utility>
#include <vector>

using namespace std;

/* These shouldn't be here, move somewhere else */

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 880;
const int SQUARE_SIZE = 40;

enum Direction {UP, DOWN, LEFT, RIGHT};

struct XY {
    int x = 0;
    int y = 0;
};

bool operator<(XY a, XY b);

/* These shouldn't be here, move somewhere else */

enum FigureType {O, I, T, S, L, J};

struct FigureVariant {
    FigureType type;
    vector<vector<XY>> rotations;
};

class Figure {
public:
    FigureVariant variant;
    char rotation;
    vector<SDL_Rect> squares;

    void initialize();
};

vector<FigureVariant> create_figures();

#endif /* FIG_HPP */
