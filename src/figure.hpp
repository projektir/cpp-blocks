#ifndef FIG_HPP
#define FIG_HPP

#include "SDL.h"
#include "SDL_image.h"
#include <utility>
#include <vector>

#include "texture.hpp"
#include "utils.hpp"
#include "context.hpp"

using namespace std;

enum FigureType {O, I, T, S, L, J};

struct FigureVariant {
    FigureType type;
    vector<vector<XY>> rotations;
};

vector<FigureVariant> create_figures();

class Figure {
public:
    FigureVariant variant;
    char rotation;
    Texture& texture;
    vector<SDL_Rect> squares;

    Figure(vector<FigureVariant> variants, Texture& texture);
    int render(Context& context);
};

#endif /* FIG_HPP */
