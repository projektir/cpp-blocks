#ifndef TEX_HPP
#define TEX_HPP

#include "SDL.h"
#include "SDL_image.h"

#include "utils.hpp"
#include "context.hpp"

class Texture {
    SDL_Texture* texture;
    SDL_Rect rect;

public:
    Texture(SDL_Texture* texture);
    int render(Context& context, SDL_Rect& dest);
};

#endif /* TEX_HPP */
