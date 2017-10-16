#ifndef FIG_HPP
#define FIG_HPP

#include "SDL.h"
#include "SDL_image.h"
#include <utility>
#include <vector>

#include "texture.hpp"
#include "stuff.hpp"
#include "context.hpp"

using namespace std;

enum FigureType {O, I, T, S, L, J};

struct FigureVariant {
    FigureType type;
    vector<vector<XY>> rotations;
};

class Figure {
public:
    FigureVariant variant;
    char rotation;
    Texture& texture;
    vector<SDL_Rect> squares;

    Figure(FigureVariant variant, Texture& texture);
    int render(Context& context);
};

vector<FigureVariant> create_figures();

#endif /* FIG_HPP */
