#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window *window = SDL_CreateWindow("cpp-blocks",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* surface = IMG_Load("C:/Projects/cpp-blocks/build/bin/Debug/square_large.png");
    if (surface == NULL ) {
        std::cout << "Unable to load image square_large.png! IMG_GetError Error: "
        << IMG_GetError() << "\n";
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}
