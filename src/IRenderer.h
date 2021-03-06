#ifndef I_RENDERER_H
#define I_RENDERER_H

#include <SDL.h>
#include <memory>
#include "Texture.h"

enum SizeMode { SIZE_IN_PIXELS,
                SIZE_IN_PERCENTAGE };
enum PositioningMode { PIN_LEFT,
                       PIN_RIGHT,
                       PIN_TOP,
                       PIN_BOTTOM,
                       PIN_CENTER };

class IRenderer {
   public:
    virtual ~IRenderer(){};
    virtual void setRenderer(SDL_Renderer* renderer, int width, int height) = 0;
    virtual SDL_Renderer* getSDLRenderer() = 0;
    virtual void clearScreen() = 0;
    virtual void renderTexture(Texture* texture, SDL_Rect* clip = nullptr, SDL_Rect* dest = nullptr, 
                               SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, SDL_Point* center = nullptr) = 0;
    virtual void renderRect(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a=255) = 0;
    virtual SDL_Rect getAbsolutePosition(Texture* texture, int x, int y, int width=-1, int height=-1,
                               PositioningMode xMode = PIN_LEFT, PositioningMode yMode = PIN_TOP,
                               SizeMode widthMode = SIZE_IN_PIXELS, SizeMode heightMode = SIZE_IN_PIXELS) = 0;
    virtual void setTextureBlendMode(Texture* texture, SDL_BlendMode blending) = 0;
    virtual void setTextureColor(Texture* texture, Uint8 red, Uint8 green, Uint8 blue) = 0;
    virtual void setTextureTransparency(Texture* texture, Uint8 opacity) = 0;
};

#endif