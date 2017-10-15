#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#include "context.hpp"
#include "figure.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 880;
const int SQUARE_SIZE = 40;

enum Direction {UP, DOWN, LEFT, RIGHT};

int start();
int move_rect(SDL_Renderer *renderer, SDL_Texture* texture,
    SDL_Rect *source_rect, SDL_Rect *dest_rect, Direction direction);

#endif /* GAME_HPP */
