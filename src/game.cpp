#include "game.hpp"

using namespace SDL2pp;

void process_key(Renderer& renderer, SDL_Keycode keycode, Figure& figure, map<XY, Texture*>& grid);

void render_grid(Renderer& render, map<XY, Texture*>& grid);
void add_figure_to_grid(const Figure& figure, map<XY, Texture*>& grid);

int start() try {
    SDL sdl(SDL_INIT_VIDEO);
    Window window("cpp-blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);    

    vector<Texture*> textures;
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
    int grid_width = SCREEN_WIDTH / SQUARE_SIZE + 2;
    int grid_height = SCREEN_HEIGHT / SQUARE_SIZE + 2;
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

    while (1) {
        renderer.Clear();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_USEREVENT:
                    if (event.user.code == FIGURE_PLACEMENT_CODE) {
                        add_figure_to_grid(figure, grid);
                        figure = Figure(figure_variants);
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

        figure.render(renderer);
        render_grid(renderer, grid);

        renderer.Present();
        
        SDL_Delay(10);
    }

    return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}

void process_key(Renderer& renderer, SDL_Keycode keycode, Figure& figure, map<XY, Texture*>& grid) {
    Direction direction;

    switch (keycode) {
        case SDLK_a:
            direction = Direction::LEFT;
            break;
        case SDLK_d:
            direction = Direction::RIGHT;
            break;
        case SDLK_s:
            direction = Direction::DOWN;
            break;
        case SDLK_w:
            direction = Direction::UP;
            break;
        case SDLK_r:
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
}
