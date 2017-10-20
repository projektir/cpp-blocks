#include "game.hpp"

using namespace SDL2pp;

void process_key(Renderer& renderer, SDL_Keycode keycode, Figure& figure, map<XY, bool>& grid);

// Temporary, grid saving will need to be reworked
void add_figure_to_grid(const Figure& figure, map<XY, bool>& grid);

int start() try {
    SDL sdl(SDL_INIT_VIDEO);
    Window window("cpp-blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);    

    vector<Texture*> textures;
    Texture o_texture(renderer, "C:/Projects/cpp-blocks/build/Debug/GreenSquare.png");
    Texture i_texture(renderer, "C:/Projects/cpp-blocks/build/Debug/RedSquare.png");
    Texture t_texture(renderer, "C:/Projects/cpp-blocks/build/Debug/BlueSquare.png");
    Texture s_texture(renderer, "C:/Projects/cpp-blocks/build/Debug/PurpleSquare.png");
    Texture l_texture(renderer, "C:/Projects/cpp-blocks/build/Debug/YellowSquare.png");
    Texture j_texture(renderer, "C:/Projects/cpp-blocks/build/Debug/OrangeSquare.png");
    textures.push_back(&o_texture);
    textures.push_back(&i_texture);
    textures.push_back(&t_texture);
    textures.push_back(&s_texture);
    textures.push_back(&l_texture);
    textures.push_back(&j_texture);

    Rect texture_rect(0, 0, SQUARE_SIZE, SQUARE_SIZE);

    renderer.SetDrawColor(0, 0, 0, 255);

    map<XY, bool> grid;
    int grid_width = SCREEN_WIDTH / SQUARE_SIZE + 1;
    int grid_height = SCREEN_HEIGHT / SQUARE_SIZE + 1;
    for (int x = -1; x < grid_width; x++) {
        for (int y = -1; y < grid_height; y++) {
            XY xy = {x, y};
            grid[xy] = false;
        }
    }

    const vector<FigureVariant> figure_variants = create_variants(textures);
    srand((unsigned int) time(0));

    vector<Figure> figures;
    figures.emplace_back(figure_variants, grid);

    SDL_Event event;

    while (1) {
        renderer.Clear();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_USEREVENT:
                    if (event.user.code == FIGURE_PLACEMENT_CODE) {
                        add_figure_to_grid(figures.back(), grid);
                        figures.emplace_back(figure_variants, grid);
                    }
                    break;
                case SDL_KEYDOWN:
                    process_key(renderer, event.key.keysym.sym, figures.back(), grid);                  

                    break;
                case SDL_QUIT:
                    return 0;
                    break;
                default:
                    break;
            }
        }

        for (auto iter = figures.begin(); iter != figures.end(); iter++) {
            (*iter).render(renderer);
        }

        renderer.Present();
    }

    return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}

void process_key(Renderer& renderer, SDL_Keycode keycode, Figure& figure, map<XY, bool>& grid) {
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

// Temporary, grid saving will need to be reworked
void add_figure_to_grid(const Figure& figure, map<XY, bool>& grid) {
    for (auto iter = figure.squares.begin(); iter != figure.squares.end(); iter++) {
        auto square = *iter;
        XY xy = {square.x / SQUARE_SIZE, square.y / SQUARE_SIZE};
        grid.at(xy) = true;
    }
}
