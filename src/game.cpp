#include "game.hpp"

Context init_context();

int cleanup(Context& context, vector<SDL_Texture*> textures);

bool process_event(Context& context, SDL_Event* event,
    Figure& figure, map<XY, bool>& grid);

void process_key(Context& context, SDL_Keycode keycode,
    Figure& figure, map<XY, bool>& grid);

int start() {
    Context context = init_context();
    
    // This vector is responsible for destroying the SDL_Textures
    vector<SDL_Texture*> textures;

    // Encapsulate image loading and texture storage
    SDL_Surface* surface = IMG_Load("C:/Projects/cpp-blocks/build/bin/Debug/green_square.png");
    if (surface == NULL ) {
        std::cout << "Unable to load image green_square.png! IMG_GetError Error: "
        << IMG_GetError() << "\n";
    }
    textures.push_back(SDL_CreateTextureFromSurface(context.renderer, surface));
    SDL_FreeSurface(surface);

    surface = IMG_Load("C:/Projects/cpp-blocks/build/bin/Debug/red_square.png");
    if (surface == NULL ) {
        std::cout << "Unable to load image red_square.png! IMG_GetError Error: "
        << IMG_GetError() << "\n";
    }
    textures.push_back(SDL_CreateTextureFromSurface(context.renderer, surface));
    SDL_FreeSurface(surface);
    // Encapsulate image loading and texture storage

    SDL_Rect source_rect;
    source_rect.x = 0;
    source_rect.y = 0;
    source_rect.w = SQUARE_SIZE;
    source_rect.h = SQUARE_SIZE;

    // In the future, this should be stored somewhere else and a
    // variant chosen at random for each new figure
    vector<FigureVariant> figures = create_figures();
    
    Texture texture2 = Texture(textures.at(0));
    Figure figure = Figure(figures[0], texture2);
    
    // Store this somewhere else
    map<XY, bool> grid;

    int grid_width = SCREEN_WIDTH / SQUARE_SIZE;
    int grid_height = SCREEN_HEIGHT / SQUARE_SIZE;
    for (int x = 0; x < grid_width; x++) {
        for (int y = 0; y < grid_height; y++) {
            XY xy = {x, y};
            grid[xy] = false;
        }
    }

    figure.render(context);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (process_event(context, &event, figure, grid)) {
                quit = true;
            }
        }
    }

    cleanup(context, textures);

    return 0;
}

Context init_context() {
    Context context;

    SDL_Init(SDL_INIT_VIDEO);

    context.window = SDL_CreateWindow("cpp-blocks",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0
    );

    context.renderer = SDL_CreateRenderer(context.window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);

    return context;
}

int cleanup(Context& context, vector<SDL_Texture*> textures) {
    for (vector<SDL_Texture*>::iterator iter = textures.begin(); iter != textures.end(); iter++) {
        SDL_DestroyTexture(*iter);
    }

    SDL_DestroyRenderer(context.renderer);
    SDL_DestroyWindow(context.window);

    SDL_Quit();

    return 0;
}

bool process_event(Context& context, SDL_Event* event,
    Figure& figure, map<XY, bool>& grid) {

    switch (event->type) {
        case SDL_KEYDOWN:
            process_key(context, event->key.keysym.sym, figure, grid);
            break;
        case SDL_USEREVENT:
            if (event->user.code == FIGURE_PLACEMENT_CODE) {
                // Place figures
            }
            break;
        case SDL_QUIT:
            return true;
            break;
        default:
            break;
    }

    return false;
}

void process_key(Context& context, SDL_Keycode keycode,
    Figure& figure, map<XY, bool>& grid) {
    
    switch (keycode) {
        case SDLK_a:
            move_figure(context, figure, grid, Direction::LEFT);
            break;
        case SDLK_d:
            move_figure(context, figure, grid, Direction::RIGHT);
            break;
        case SDLK_s:
            move_figure(context, figure, grid, Direction::DOWN);
            break;
        case SDLK_w:
            move_figure(context, figure, grid, Direction::UP);
            break;
        default:
            break;
    }
}

bool will_collide(Figure& figure, map<XY, bool>& grid, Direction direction) {
    bool colliding = false;
    
    for (int i = 0; i < figure.squares.size(); i++) {
        SDL_Rect& rect = figure.squares.at(i);

        SDL_Rect test_rect;
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

                    SDL_Event figure_planted;                    
                    figure_planted.type = SDL_USEREVENT;
                    figure_planted.user.code = FIGURE_PLACEMENT_CODE;
                    SDL_PushEvent(&figure_planted);
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

int move_figure(Context& context, Figure& figure, map<XY, bool>& grid, Direction direction) {
    SDL_RenderClear(context.renderer);

    if (will_collide(figure, grid, direction)) {
        return 0;
    }

    for (int i = 0; i < figure.squares.size(); i++) {
        SDL_Rect& rect = figure.squares.at(i);

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

    figure.render(context);

    return 0;
}
