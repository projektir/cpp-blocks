#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

const int SQUARE_SIZE = 20;

enum Direction {UP, DOWN, LEFT, RIGHT};

int init();
int move_rect(SDL_Renderer *renderer, SDL_Texture* texture,
    SDL_Rect *source_rect, SDL_Rect *dest_rect, Direction direction);

#endif /* GAME_HPP */
