#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#include "Texture.h"
#include "Sprite.h"


Sprite::Sprite() {
    mTexture = nullptr;
    mClip.x = 0;
    mClip.y = 0;
    mClip.w = 0;
    mClip.h = 0;
}

Sprite::Sprite(Texture* texture, int x, int y, int w, int h, bool defaultHitbox) {
    setSprite(texture, x, y, w, h, defaultHitbox);
}

void Sprite::setSprite(Texture* texture, int x, int y, int w, int h, bool defaultHitbox) {
    mTexture = texture;
    mClip.x = x;
    mClip.y = y;
    mClip.w = w;
    mClip.h = h;
    if(defaultHitbox == true) addProportionalHitbox(0, 0, 1.0, 1.0);
}


SDL_Rect* Sprite::getClip() {
    return &mClip;
}

Texture* Sprite::getTexture() {
    return mTexture;
}

std::vector<ProportionalRectangle>& Sprite::getProportionalHitboxes() {
    return mProportionalHitboxes;
}

Sprite& Sprite::addProportionalHitbox(double xScale, double yScale, double wScale, double hScale) {
    mProportionalHitboxes.emplace_back(xScale, yScale, wScale, hScale);
    return *this;
}

Sprite& Sprite::addProportionalHurtbox(double xScale, double yScale, double wScale, double hScale) {
    mProportionalHurtboxes.emplace_back(xScale, yScale, wScale, hScale);
    return *this;
}