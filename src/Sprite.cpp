#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#include "Texture.h"
#include "Sprite.h"

Sprite::Sprite(Texture* texture, int x, int y, int w, int h, bool defaultHitbox) {
    mTexture = texture;
    mClip.x = x;
    mClip.y = y;
    mClip.w = w;
    mClip.h = h;
    if(defaultHitbox == true) addHitbox(0, 0, w, h);
}

SDL_Rect* Sprite::getClip() {
    return &mClip;
}

Texture* Sprite::getTexture() {
    return mTexture;
}

std::vector<SDL_Rect>* Sprite::getHitboxes() {
    return &mHitboxes;
}

bool Sprite::hasHitboxes() const {
    return (mHitboxes.size() > 0);
}

void Sprite::addHitbox(int x, int y, int w, int h) {
    SDL_Rect newRect{x, y, w, h};
    mHitboxes.push_back(newRect);
}