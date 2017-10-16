#ifndef FIG_HPP
#define FIG_HPP

#include <map>
#include <vector>
#include <exception>

#include "SDL.h"

#include <SDL2pp/SDL2pp.hh>

#include "utils.hpp"
#include "figure_variant.hpp"

using namespace std;

class Figure {
    bool will_collide(map<XY, bool>& grid, Direction direction);
public:
    FigureVariant* variant;
    char rotation;
    vector<Rect> squares;

    Figure(FigureVariant* variant);

    int render(Renderer& renderer);
    void move_figure(map<XY, bool>& grid, Direction direction);

    static Figure random(const vector<FigureVariant>& figure_variants);
};

#endif /* FIG_HPP */
