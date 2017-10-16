#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <map>

#include "figure.hpp"

int start();
bool will_collide(Figure& figure, map<XY, bool>& grid, Direction direction);
int move_figure(Context& context, Figure& figure, map<XY, bool>& grid, Direction direction);

#endif /* GAME_HPP */
