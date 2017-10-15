#include "game.hpp"

Context init_ctx();

int cleanup(Context* context, SDL_Texture* texture);

bool process_event(SDL_Event* event,
    SDL_Renderer* renderer, SDL_Texture* texture,
    SDL_Rect* source_rect, SDL_Rect* dest_rect);

void process_key(SDL_Keycode keycode,
    SDL_Renderer* renderer, SDL_Texture* texture,
    SDL_Rect* source_rect, SDL_Rect* dest_rect);

int start() {
    Context ctx = init_ctx();

    vector<FigureVariant> figures = create_figures();

    if (!figures.empty()) {
        FigureVariant current_variant = figures[0];
    }

    XY figure_location = {0, 0};

    SDL_Rect source_rect;
    SDL_Rect dest_rect;

    source_rect.x = 0;
    source_rect.y = 0;
    source_rect.w = SQUARE_SIZE;
    source_rect.h = SQUARE_SIZE;

    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.w = SQUARE_SIZE;
    dest_rect.h = SQUARE_SIZE;    

    SDL_Surface* surface = IMG_Load("C:/Projects/cpp-blocks/build/bin/Debug/square.png");
    if (surface == NULL ) {
        std::cout << "Unable to load image square_large.png! IMG_GetError Error: "
        << IMG_GetError() << "\n";
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx.renderer, surface);

    SDL_FreeSurface(surface);

    SDL_RenderCopy(ctx.renderer, texture, &source_rect, &dest_rect);
    SDL_RenderPresent(ctx.renderer);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (process_event(&event, ctx.renderer, texture, &source_rect, &dest_rect)) {
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
    SDL_Rect* source_rect, SDL_Rect* dest_rect) {

    switch (event->type) {
        case SDL_KEYDOWN:
            process_key(event->key.keysym.sym, renderer, texture,
                source_rect, dest_rect);
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
    SDL_Rect* source_rect, SDL_Rect* dest_rect) {
    
    switch (keycode) {
        case SDLK_a:
            move_rect(renderer, texture, source_rect, dest_rect,
                Direction::LEFT);
            break;
        case SDLK_d:
            move_rect(renderer, texture, source_rect, dest_rect,
                Direction::RIGHT);
            break;
        case SDLK_s:
            move_rect(renderer, texture, source_rect, dest_rect,
                Direction::DOWN);
            break;
        case SDLK_w:
            move_rect(renderer, texture, source_rect, dest_rect,
                Direction::UP);
            break;
        default:
            break;
    }
}

// Convert this to a move-figure later
int move_rect(SDL_Renderer* renderer, SDL_Texture* texture,
    SDL_Rect* source_rect, SDL_Rect* dest_rect, Direction direction) {

    SDL_RenderClear(renderer);

    switch (direction) {
        case Direction::UP:
            dest_rect->y -= SQUARE_SIZE;
            break;
        case Direction::DOWN:
            dest_rect->y += SQUARE_SIZE;
            break;
        case Direction::LEFT:
            dest_rect->x -= SQUARE_SIZE;
            break;
        case Direction::RIGHT:
            dest_rect->x += SQUARE_SIZE;
            break;
    }

    SDL_RenderCopy(renderer, texture, source_rect, dest_rect);
    SDL_RenderPresent(renderer);

    return 0;
}
