#ifndef CTX_HPP
#define CTX_HPP

#include "SDL.h"
#include "SDL_image.h"

class Context {
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif /* CTX_HPP */
