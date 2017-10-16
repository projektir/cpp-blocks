#include "texture.hpp"

Texture::Texture(SDL_Texture* texture) {
    this->texture = texture;
    
    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.w = SQUARE_SIZE;
    this->rect.h = SQUARE_SIZE;
}

int Texture::render(Context& context, SDL_Rect& dest) {
    SDL_RenderCopy(context.renderer, texture, &rect, &dest);
    SDL_RenderPresent(context.renderer);

    return 0;
}
