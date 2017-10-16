#ifndef FIG_VAR_HPP
#define FIG_VAR_HPP

#include <vector>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

#include "utils.hpp"

using namespace std;
using namespace SDL2pp;

enum FigureType {O, I, T, S, L, J};

class FigureVariant {
public:
    FigureType type;
    Texture* texture;
    vector<vector<XY>> rotations;
};

vector<FigureVariant> create_variants(vector<Texture*> textures);

#endif /* FIG_VAR_HPP */
