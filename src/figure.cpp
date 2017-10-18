#include "figure.hpp"

Figure::Figure(const vector<FigureVariant>& figure_variants) {
    auto variant_index = rand() % figure_variants.size();
    auto random_variant = figure_variants.at(variant_index);

    this->variant = random_variant;
    this->rotation = 0;

    auto rotations = this->variant.rotations[rotation];

    for (auto iter = rotations.begin(); iter != rotations.end(); iter++) {
        auto rotation_offsets = *iter;

        Rect rect;
        rect.x = (rotation_offsets.x * SQUARE_SIZE);
        rect.y = (rotation_offsets.y * SQUARE_SIZE);
        rect.w = SQUARE_SIZE;
        rect.h = SQUARE_SIZE;

        this->squares.push_back(rect);
    }
}

int Figure::render(Renderer& renderer)  try {
    for (auto iter = squares.begin(); iter != squares.end(); iter++) {
        renderer.Copy(*(variant.texture), NullOpt, *iter);
    }

    return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}

void Figure::move_figure(map<XY, bool>& grid, Direction direction) {
    if (will_collide(grid, direction)) {
        return;
    }

    for (auto iter = this->squares.begin(); iter != this->squares.end(); iter++) {
        Rect& rect = *iter;

        switch (direction) {
            case Direction::UP:
                rect.y -= SQUARE_SIZE;
                break;
            case Direction::DOWN:
                rect.y += SQUARE_SIZE;
                break;
            case Direction::LEFT:
                rect.x -= SQUARE_SIZE;
                break;
            case Direction::RIGHT:
                rect.x += SQUARE_SIZE;
                break;
        }
    }
}

bool Figure::will_collide(map<XY, bool>& grid, Direction direction) {
    bool colliding = false;
    
    for (auto iter = this->squares.begin(); iter != this->squares.end(); iter++) {
        Rect& rect = *iter;

        Rect test_rect;
        test_rect.x = rect.x;
        test_rect.y = rect.y;

        switch (direction) {
            case Direction::UP:
                test_rect.y -= SQUARE_SIZE;
                if (test_rect.y >= SCREEN_HEIGHT || test_rect.y < 0) {
                    colliding = true;
                }                
                break;
            case Direction::DOWN:
                test_rect.y += SQUARE_SIZE;
                if (test_rect.y >= SCREEN_HEIGHT || test_rect.y < 0) {
                    colliding = true;

                    SDL_Event figure_placed;                    
                    figure_placed.type = SDL_USEREVENT;
                    figure_placed.user.code = FIGURE_PLACEMENT_CODE;
                    SDL_PushEvent(&figure_placed);
                }
                break;
            case Direction::LEFT:
                test_rect.x -= SQUARE_SIZE;
                if (test_rect.x >= SCREEN_WIDTH || test_rect.x < 0) {
                    colliding = true;
                }
                break;
            case Direction::RIGHT:
                test_rect.x += SQUARE_SIZE;
                if (test_rect.x >= SCREEN_WIDTH || test_rect.x < 0) {
                    colliding = true;
                }
                break;
        }

        if (!colliding) {
            XY xy = {test_rect.x / SQUARE_SIZE, test_rect.y / SQUARE_SIZE};
            if (grid[xy]) {
                colliding = true;
            }
        }
    }

    return colliding;
}
