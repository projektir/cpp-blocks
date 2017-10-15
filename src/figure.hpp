#ifndef FIG_HPP
#define FIG_HPP

#include "SDL.h"
#include "SDL_image.h"
#include <utility>
#include <vector>

using namespace std;

struct XY {
    int x;
    int y;
};

enum Figure {O, I, T, S, L, J};

struct FigureVariant {
    Figure type;
    vector<vector<XY>> rotations;
};

vector<FigureVariant> create_figures();

#endif /* FIG_HPP */
