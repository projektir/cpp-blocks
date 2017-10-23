#ifndef FIG_VAR_HPP
#define FIG_VAR_HPP

#include <vector>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

#include "utils.hpp"

enum FigureType {O, I, T, S, L, J};

class FigureVariant {
    
public:
    FigureType type;
    SDL2pp::Texture* texture;
    std::vector<std::vector<XY>> rotations;
};

std::vector<FigureVariant> create_variants(std::vector<SDL2pp::Texture*> textures);

#endif /* FIG_VAR_HPP */
