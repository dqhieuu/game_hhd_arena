#include <SDL.h>
#include "Sprite.h"
#include "Texture.h"

bool checkCollision(SDL_Rect &a, SDL_Rect &b) {
    if (SDL_HasIntersection(&a, &b) == SDL_TRUE) return true;
    return false;
}

bool getCollision(SDL_Rect &a, SDL_Rect &b, SDL_Rect &res) {
    if (SDL_IntersectRect(&a, &b, &res) == SDL_TRUE) return true;
    return false;
}