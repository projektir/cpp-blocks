#include "game.hpp"

using namespace SDL2pp;

void process_key(Renderer& renderer, SDL_Keycode keycode, Figure& figure, map<XY, bool>& grid);

int start() try {
    SDL sdl(SDL_INIT_VIDEO);
    Window window("cpp-blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);    

    vector<Texture*> textures;
    Texture o_texture(renderer, "C:/Users/Nidhogg/Pictures/GreenSquare.png");
    Texture i_texture(renderer, "C:/Users/Nidhogg/Pictures/RedSquare.png");
    textures.push_back(&o_texture);
    textures.push_back(&i_texture);

    Rect texture_rect(0, 0, SQUARE_SIZE, SQUARE_SIZE);

    renderer.SetDrawColor(0, 0, 0, 255);

    const vector<FigureVariant> figure_variants = create_variants(textures);
    srand((unsigned int) time(0));

    vector<Figure> figures;
    
    auto variant_index = rand() % figure_variants.size();
    auto random_variant = figure_variants.at(variant_index);
    figures.emplace_back(&random_variant);

    map<XY, bool> grid;
    int grid_width = SCREEN_WIDTH / SQUARE_SIZE;
    int grid_height = SCREEN_HEIGHT / SQUARE_SIZE;
    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++) {
            XY xy = {x, y};
            grid[xy] = false;
        }
    }

    figures.back().render(renderer);

    SDL_Event event;

    while (1) {
        renderer.Clear();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    process_key(renderer, event.key.keysym.sym, figures.back(), grid);                  

                    break;
                case SDL_USEREVENT:
                    if (event.user.code == FIGURE_PLACEMENT_CODE) {
                        //placed_figures.push_back(current_figure);
                        //current_figure = generate_random_figure(figure_variants);
                    }
                    break;
                case SDL_QUIT:
                    return 0;
                    break;
                default:
                    break;
            }
        }
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
        default:
            break;
    }

    figure.move_figure(grid, direction);
    figure.render(renderer);
}
