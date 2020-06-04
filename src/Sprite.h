#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include <vector>
#include <unordered_map>

struct ProportionalRectangle {
    double x,y,w,h;
    ProportionalRectangle(double _x, double _y, double _w, double _h):x(_x),y(_y),w(_w), h(_h) {}
    SDL_Rect getMultipliedRect(SDL_Rect &rect) {
        return SDL_Rect {static_cast<int>(rect.x + x*rect.w), static_cast<int>(rect.y + y*rect.h), static_cast<int>(w*rect.w), static_cast<int>(h*rect.h)};
    }
};


class Sprite {
   public:
    Sprite();
    Sprite(Texture* texture, int x, int y, int w, int h, bool defaultHitBox=false);
    void setSprite(Texture* texture, int x, int y, int w, int h, bool defaultHitBox=false);
    Texture* getTexture();
    SDL_Rect* getClip();
    Sprite& addProportionalHitbox(double xScale, double yScale, double wScale, double hScale);
    Sprite& addProportionalHurtbox(double xScale, double yScale, double wScale, double hScale);
    inline bool hasHitboxes() const;
    std::vector<ProportionalRectangle>& getProportionalHitboxes();
   private:
    Texture* mTexture;
    SDL_Rect mClip;
    std::vector<ProportionalRectangle> mProportionalHitboxes;
    std::vector<ProportionalRectangle> mProportionalHurtboxes;
};

typedef std::vector<Sprite> SpriteCollection;
typedef std::unordered_map<std::string, SpriteCollection> SpriteDictionary;

#endif