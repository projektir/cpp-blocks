#include "game.hpp"

using std::map;
using std::vector;

using SDL2pp::NullOpt;
using SDL2pp::Texture;
using SDL2pp::Rect;
using SDL2pp::Renderer;

namespace ch = std::chrono;
using timer = ch::steady_clock;

void process_key(Renderer& renderer, SDL_Keycode keycode, Figure& figure, map<XY, Texture*>& grid);

void render_grid(Renderer& render, map<XY, Texture*>& grid);
void add_figure_to_grid(const Figure& figure, map<XY, Texture*>& grid);

int start() try {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window("cpp-blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);    

    std::vector<Texture*> textures;
    Texture o_texture(renderer, "images/GreenSquare.png");
    Texture i_texture(renderer, "images/RedSquare.png");
    Texture t_texture(renderer, "images/BlueSquare.png");
    Texture s_texture(renderer, "images/PurpleSquare.png");
    Texture l_texture(renderer, "images/YellowSquare.png");
    Texture j_texture(renderer, "images/OrangeSquare.png");
    textures.push_back(&o_texture);
    textures.push_back(&i_texture);
    textures.push_back(&t_texture);
    textures.push_back(&s_texture);
    textures.push_back(&l_texture);
    textures.push_back(&j_texture);

    Rect texture_rect(0, 0, SQUARE_SIZE, SQUARE_SIZE);

    renderer.SetDrawColor(0, 0, 0, 255);

    map<XY, Texture*> grid;
    int grid_width = WIDTH + 2;
    int grid_height = HEIGHT + 2;
    for (int x = -1; x < grid_width; x++) {
        for (int y = -1; y < grid_height; y++) {
            XY xy = {x, y};
            grid[xy] = nullptr;
        }
    }

    const vector<FigureVariant> figure_variants = create_variants(textures);
    srand((unsigned int) time(0));

    Figure figure(figure_variants);

    SDL_Event event;

    auto start = timer::now();
    auto drop_start = start;

    while (1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_USEREVENT:
                    if (event.user.code == FIGURE_PLACEMENT_CODE) {
                        add_figure_to_grid(figure, grid);
                        figure = Figure(figure_variants);

                        auto elapsed = ch::duration_cast<ch::milliseconds>(timer::now() - start);
                        if (elapsed >= SPEED_INCREASE_INTERVAL) {
                            
                            start = timer::now();
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    process_key(renderer, event.key.keysym.sym, figure, grid);                  

                    break;
                case SDL_QUIT:
                    return 0;
                    break;
                default:
                    break;
            }
        }

        renderer.Clear();
        
        auto elapsed = ch::duration_cast<ch::milliseconds>(timer::now() - drop_start);
        if (elapsed >= FALL_SPEED_INTERVAL_START) {
            figure.move(grid, Direction::DOWN);
            drop_start = timer::now();
        }

        figure.render(renderer);
        render_grid(renderer, grid);

        renderer.Present();
        
        SDL_Delay(10);
    }

    return 0;
} catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	return 1;
}

void process_key(Renderer& renderer, SDL_Keycode keycode, Figure& figure, map<XY, Texture*>& grid) {
    Direction direction;

    switch (keycode) {
        case SDLK_a:
        case SDLK_LEFT:
            direction = Direction::LEFT;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            direction = Direction::RIGHT;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            direction = Direction::DOWN;
            break;
        case SDLK_r:
        case SDLK_UP:
            figure.rotate(grid);
            return;
        default:
            break;
    }

    figure.move(grid, direction);
    figure.render(renderer);
}

void render_grid(Renderer& render, map<XY, Texture*>& grid) {
    for (const auto &pair : grid) {
        if (pair.second != nullptr) {
            auto loc = pair.first;
            render.Copy(*(pair.second), NullOpt,
                Rect(loc.x * SQUARE_SIZE, loc.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE));
        }
    }
}

void add_figure_to_grid(const Figure& figure, map<XY, Texture*>& grid) {
    for (auto iter = figure.squares.begin(); iter != figure.squares.end(); iter++) {
        auto square = *iter;
        XY xy = {square.x / SQUARE_SIZE, square.y / SQUARE_SIZE};
        grid.at(xy) = figure.variant.texture;
    }

    bool filled_row = true;
    for (int y = 0; y < HEIGHT; y++) {
        filled_row = true;
        for (int x = 0; x < WIDTH; x++) {
            if (grid.at(XY{x, y}) == nullptr) {
                filled_row = false;
                break;
            }
        }

        if (filled_row) {
            int filled_y = y;
            for (int y = filled_y; y > 0; y--) {
                for (int x = 0; x < WIDTH; x++) {
                    grid.at(XY{x, y}) = grid.at(XY{x, y - 1});
                }
            }
        }
    }
}
