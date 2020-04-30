#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include <vector>

class Sprite {
   public:
    Sprite(Texture* texture, int x, int y, int w, int h, bool defaultHitBox=false);
    ~Sprite();
    Texture* getTexture();
    SDL_Rect* getClip();
    void addHitbox(int x, int y, int w, int h);
    inline bool hasHitboxes() const;
    std::vector<SDL_Rect>* getHitboxes();
   private:
    Texture* mTexture;
    SDL_Rect mClip;
    std::vector<SDL_Rect> mHitboxes;
};

#endif