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
    bool will_collide(const map<XY, Texture*>& grid, Direction direction);
    void set_squares();

    static bool collides_with_grid(const map<XY, Texture*>& grid, const Rect test_rect);
public:
    FigureVariant variant;
    char rotation;
    vector<Rect> squares;

    Figure(const vector<FigureVariant>& figure_variants);

    int render(Renderer& renderer);
    void move(const map<XY, Texture*>& grid, Direction direction);
    void rotate(const map<XY, Texture*>& grid);
};

#endif /* FIG_HPP */
