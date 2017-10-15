#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <map>

#include "context.hpp"
#include "figure.hpp"

int start();
int draw_figure(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Rect& source_rect, Figure& figure);
int move_figure(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Rect *source_rect, Figure& figure, Direction direction);

#endif /* GAME_HPP */
