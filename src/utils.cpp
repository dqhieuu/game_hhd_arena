#include <Sprite.h>

bool checkCollision(Sprite &a, Sprite &b) {
    std::vector<SDL_Rect> *aHitboxes = a.getHitboxes();
    std::vector<SDL_Rect> *bHitboxes = b.getHitboxes();
    SDL_Rect result;
    for(auto it1 = (*aHitboxes).begin(); it1 != (*aHitboxes).end(); ++it1)
        for(auto it2 = (*bHitboxes).begin(); it1 != (*bHitboxes).end(); ++it1) 
            if (SDL_IntersectRect(&(*it1), &(*it2), &result) == SDL_TRUE) return true;
    return false;
}