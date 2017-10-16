#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <map>

#include "context.hpp"
#include "figure.hpp"

int start();
bool will_collide(Figure& figure, map<XY, bool>& grid, Direction direction);
int draw_figure(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Rect& source_rect, Figure& figure);
int move_figure(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Rect& source_rect, Figure& figure, map<XY, bool>& grid, Direction direction);

#endif /* GAME_HPP */
