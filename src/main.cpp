#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

const int SQUARE_SIZE = 40;
enum Direction {UP, DOWN, LEFT, RIGHT};

int move_square();

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window *window = SDL_CreateWindow("cpp-blocks",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
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
    SDL_Keycode keycode;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    keycode = event.key.keysym.sym;
                        case SDLK_a:
                        case SDLK_w:
                        case SDLK_s:
                            std::cout << "The S key has been pressed." << std::endl;
                            SDL_RenderClear(renderer);
                            dest_rect.y += SQUARE_SIZE;
                            SDL_RenderCopy(renderer, texture, &source_rect, &dest_rect);
                            SDL_RenderPresent(renderer);
                        case SDLK_d:
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}

int move_square() {
    return 0;
}
