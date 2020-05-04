#include <SDL.h>
#include "Sprite.h"
#include "Texture.h"

bool checkCollision(SDL_Rect &a, SDL_Rect &b) {
    SDL_Rect result;
    if (SDL_IntersectRect(&a, &b, &result) == SDL_TRUE) return true;
    return false;
}
