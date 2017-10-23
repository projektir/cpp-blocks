#ifndef FIG_HPP
#define FIG_HPP

#include <map>
#include <vector>
#include <exception>

#include "SDL.h"

#include <SDL2pp/SDL2pp.hh>

#include "utils.hpp"
#include "figure_variant.hpp"

class Figure {
    //using vector = std::vector;
    //using map = std::map;

    using Rect = SDL2pp::Rect;
    using Renderer = SDL2pp::Renderer;
    using Texture = SDL2pp::Texture;

    bool will_collide(const std::map<XY, Texture*>& grid, Direction direction);
    static bool collides_with_grid(const std::map<XY, Texture*>& grid, const Rect test_rect);
public:
    FigureVariant variant;
    char rotation;
    std::vector<Rect> squares;

    Figure(const std::vector<FigureVariant>& figure_variants);

    int render(Renderer& renderer);
    void move(const std::map<XY, Texture*>& grid, Direction direction);
    void rotate(const std::map<XY, Texture*>& grid);
};

#endif /* FIG_HPP */
