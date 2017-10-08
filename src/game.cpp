#include "game.hpp"

bool process_event(SDL_Event* event,
    SDL_Renderer *renderer, SDL_Texture* texture,
    SDL_Rect *source_rect, SDL_Rect *dest_rect);

void process_key(SDL_Keycode keycode,
    SDL_Renderer *renderer, SDL_Texture* texture,
    SDL_Rect *source_rect, SDL_Rect *dest_rect);

int init() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("cpp-blocks",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 880,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, &source_rect, &dest_rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(300);


    SDL_RenderClear(renderer);
    dest_rect.x = 40;
    dest_rect.y = 40;
    SDL_RenderCopy(renderer, texture, &source_rect, &dest_rect);
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (process_event(&event, renderer, texture, &source_rect, &dest_rect)) {
                quit = true;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

bool process_event(SDL_Event* event,
    SDL_Renderer *renderer, SDL_Texture* texture,
    SDL_Rect *source_rect, SDL_Rect *dest_rect) {

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
    SDL_Renderer *renderer, SDL_Texture* texture,
    SDL_Rect *source_rect, SDL_Rect *dest_rect) {
    
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
int move_rect(SDL_Renderer *renderer, SDL_Texture* texture,
    SDL_Rect *source_rect, SDL_Rect *dest_rect, Direction direction) {

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
