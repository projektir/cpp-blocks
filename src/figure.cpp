#include "figure.hpp"

using std::vector;

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;

Figure::Figure(const std::vector<FigureVariant>& figure_variants) {
    auto variant_index = rand() % figure_variants.size();
    auto random_variant = figure_variants.at(variant_index);

    this->variant = random_variant;
    this->rotation = 0;

    auto rotations = this->variant.rotations[this->rotation];
    
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

int Figure::render(Renderer& renderer) try {
    for (auto iter = squares.begin(); iter != squares.end(); iter++) {
        renderer.Copy(*(variant.texture), NullOpt, *iter);
    }

    return 0;
} catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	return 1;
}

void Figure::move(const std::map<XY, Texture*>& grid, Direction direction) {
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

bool Figure::will_collide(const std::map<XY, Texture*>& grid, Direction direction) {
    bool colliding = false;
    
    for (auto iter = this->squares.begin(); iter != this->squares.end(); iter++) {
        Rect& rect = *iter;

        Rect test_rect;
        test_rect.x = rect.x;
        test_rect.y = rect.y;

        switch (direction) {
            case Direction::UP:
                test_rect.y -= SQUARE_SIZE;

                if (collides_with_grid(grid, test_rect) ||
                    test_rect.y >= SCREEN_HEIGHT || test_rect.y < 0) {

                    colliding = true;
                }

                break;
            case Direction::DOWN:
                test_rect.y += SQUARE_SIZE;

                if (collides_with_grid(grid, test_rect) ||
                    test_rect.y >= SCREEN_HEIGHT || test_rect.y < 0) {

                    SDL_Event figure_placed;
                    
                    if (SDL_PeepEvents(&figure_placed, 1, SDL_PEEKEVENT, SDL_USEREVENT, SDL_USEREVENT) == 0) {
                        figure_placed.type = SDL_USEREVENT;
                        figure_placed.user.code = FIGURE_PLACEMENT_CODE;
                        SDL_PushEvent(&figure_placed);
                    }
                    
                    colliding = true;
                }

                break;
            case Direction::LEFT:
                test_rect.x -= SQUARE_SIZE;

                if (collides_with_grid(grid, test_rect) ||
                    test_rect.x >= SCREEN_WIDTH || test_rect.x < 0) {
                    
                    colliding = true;
                }

                break;
            case Direction::RIGHT:
                test_rect.x += SQUARE_SIZE;

                if (collides_with_grid(grid, test_rect) ||
                    test_rect.x >= SCREEN_WIDTH || test_rect.x < 0) {
                    
                        colliding = true;
                }

                break;
        }
    }

    return colliding;
}

bool Figure::collides_with_grid(const std::map<XY, Texture*>& grid, const Rect test_rect) {
    XY xy = {test_rect.x / SQUARE_SIZE, test_rect.y / SQUARE_SIZE};
    if (grid.at(xy) != nullptr) {
        return true;
    }

    return false;
}

void Figure::rotate(const std::map<XY, Texture*>& grid) {
    auto new_rotation = this->rotation;
    
    {
        auto rotations = this->variant.rotations;

        if (new_rotation < rotations.size() - 1) {
            new_rotation++;
        } else {
            new_rotation = 0;
        }
    }

    auto rotations = this->variant.rotations[new_rotation];
    
    Rect old_rect;
    if (this->squares.size() > 0) {
        old_rect = this->squares.front();
    }

    std::vector<Rect> new_squares;

    for (auto iter = rotations.begin(); iter != rotations.end(); iter++) {
        auto rotation_offsets = *iter;

        Rect rect;
        rect.x = (rotation_offsets.x * SQUARE_SIZE) + old_rect.x;
        rect.y = (rotation_offsets.y * SQUARE_SIZE) + old_rect.y;
        rect.w = SQUARE_SIZE;
        rect.h = SQUARE_SIZE;

        if (collides_with_grid(grid, rect) ||
            (rect.y >= SCREEN_HEIGHT || rect.y < 0) ||
            (rect.y >= SCREEN_HEIGHT || rect.y < 0) ||
            (rect.x >= SCREEN_WIDTH  || rect.x < 0) ||
            (rect.x >= SCREEN_WIDTH  || rect.x < 0)) {
            return;
        }

        new_squares.push_back(rect);
    }

    this->rotation = new_rotation;
    this->squares = new_squares;
}
