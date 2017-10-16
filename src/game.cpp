#include "game.hpp"

Context init_ctx();

int cleanup(Context* context, SDL_Texture* texture);

bool process_event(SDL_Event* event,
    SDL_Renderer* renderer, SDL_Texture* texture,
    Figure& figure, map<XY, bool>& grid, SDL_Rect& source_rect);

void process_key(SDL_Keycode keycode,
    SDL_Renderer* renderer, SDL_Texture* texture,
    Figure& figure, map<XY, bool>& grid, SDL_Rect& source_rect);

int start() {
    Context ctx = init_ctx();
    vector<FigureVariant> figures = create_figures();

    Figure figure;
    // Remove this when figures are generated randomly
    figure.variant = figures[0];

    figure.initialize();

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

    SDL_Surface* surface = IMG_Load("C:/Projects/cpp-blocks/build/bin/Debug/square.png");
    if (surface == NULL ) {
        std::cout << "Unable to load image square.png! IMG_GetError Error: "
        << IMG_GetError() << "\n";
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx.renderer, surface);

    SDL_FreeSurface(surface);

    SDL_Rect source_rect;
    source_rect.x = 0;
    source_rect.y = 0;
    source_rect.w = SQUARE_SIZE;
    source_rect.h = SQUARE_SIZE;

    draw_figure(ctx.renderer, texture, source_rect, figure);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            // OK need to stop sticking lots and lots of things into this poor function call
            if (process_event(&event, ctx.renderer, texture, figure, grid, source_rect)) {
                quit = true;
            }
        }
    }

    cleanup(&ctx, texture);

    return 0;
}

Context init_ctx() {
    Context ctx;

    ctx.renderer = nullptr;
    ctx.window = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    ctx.window = SDL_CreateWindow("cpp-blocks",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0
    );

    ctx.renderer = SDL_CreateRenderer(ctx.window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);

    return ctx;
}

int cleanup(Context* context, SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(context->renderer);
    SDL_DestroyWindow(context->window);

    context->renderer = nullptr;
    context->window = nullptr;

    SDL_Quit();

    return 0;
}

bool process_event(SDL_Event* event,
    SDL_Renderer* renderer, SDL_Texture* texture,
    Figure& figure, map<XY, bool>& grid, SDL_Rect& source_rect) {

    switch (event->type) {
        case SDL_KEYDOWN:
            process_key(event->key.keysym.sym, renderer, texture,
                figure, grid, source_rect);
            break;
        case SDL_QUIT:
            return true;
            break;
        default:
            break;
    }

    return false;
}

void process_key(SDL_Keycode keycode,
    SDL_Renderer* renderer, SDL_Texture* texture,
    Figure& figure, map<XY, bool>& grid, SDL_Rect& source_rect) {
    
    switch (keycode) {
        case SDLK_a:
            move_figure(renderer, texture, source_rect, figure, grid, Direction::LEFT);
            break;
        case SDLK_d:
            move_figure(renderer, texture, source_rect, figure, grid, Direction::RIGHT);
            break;
        case SDLK_s:
            move_figure(renderer, texture, source_rect, figure, grid, Direction::DOWN);
            break;
        case SDLK_w:
            move_figure(renderer, texture, source_rect, figure, grid, Direction::UP);
            break;
        default:
            break;
    }
}

int draw_figure(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Rect& source_rect, Figure& figure) {
    for (int i = 0; i < figure.squares.size(); i++) {
        auto rect = figure.squares[i];
        SDL_RenderCopy(renderer, texture, &source_rect, &rect);
    }

    SDL_RenderPresent(renderer);

    return 0;
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
            XY xy;
            xy.x = test_rect.x;
            xy.y = test_rect.y;
            if (grid[xy]) {
                colliding = true;
            }
        }
    }

    return colliding;
}

int move_figure(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Rect& source_rect, Figure& figure, map<XY, bool>& grid, Direction direction) {
    SDL_RenderClear(renderer);

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

        SDL_RenderCopy(renderer, texture, &source_rect, &rect);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
