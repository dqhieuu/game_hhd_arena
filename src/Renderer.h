#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "Texture.h"
#include "IRenderer.h"



class Renderer : public IRenderer {
   public:
    Renderer();
    virtual void setRenderer(SDL_Renderer* renderer, int width, int height);
    virtual SDL_Renderer* getSDLRenderer();
    virtual void clearScreen();
    virtual void renderTexture(Texture* texture, int x, int y, int width = -1, int height = -1, SDL_Rect* clip = nullptr,
                               PositioningMode xMode = PIN_LEFT, PositioningMode yMode = PIN_TOP,
                               SizeMode widthMode = SIZE_IN_PIXELS, SizeMode heightMode = SIZE_IN_PIXELS,
                               SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, SDL_Point* center = nullptr);
    virtual void setTextureBlendMode(Texture* texture, SDL_BlendMode blending);
    virtual void setTextureColor(Texture* texture, Uint8 red, Uint8 green, Uint8 blue);
    virtual void setTextureTransparency(Texture* texture, Uint8 opacity);
   private:
    SDL_Renderer* mRenderer;
    int mWindowWidth;
    int mWindowHeight;
};

#endif