#include "IRenderer.h"
#include "Renderer.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

#include "Texture.h"

Renderer::Renderer() {
    mRenderer = nullptr;
    mWindowWidth = mWindowHeight = 0;
}

void Renderer::setRenderer(SDL_Renderer* renderer, int width, int height) {
    mRenderer = renderer;
    mWindowWidth = width;
    mWindowHeight = height;
}

SDL_Renderer* Renderer::getSDLRenderer() {
    return mRenderer;
}
void Renderer::clearScreen() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}

void Renderer::renderTexture(Texture* texture, int x, int y, int width, int height, SDL_Rect* clip,
                             PositioningMode xMode, PositioningMode yMode,
                             SizeMode widthMode, SizeMode heightMode,
                             SDL_RendererFlip flip, double angle, SDL_Point* center) {
    if (texture == nullptr) return;
    if (width != -1) {
        if (widthMode == SIZE_IN_PERCENTAGE) {
            width = (mWindowWidth * width) / 100;
        }
    } else
        width = texture->getWidth();
    if (height != -1) {
        if (heightMode == SIZE_IN_PERCENTAGE) {
            height = (mWindowHeight * height) / 100;
        }
    } else
        height = texture->getHeight();
    if (xMode == PIN_RIGHT) {
        x = mWindowWidth - (x + width + 1);
    } else if (xMode == PIN_CENTER) {
        x = (mWindowWidth - width) / 2 + x;
    }
    if (yMode == PIN_BOTTOM) {
        y = mWindowHeight - (y + height + 1);
    } else if (yMode == PIN_CENTER) {
        y = (mWindowHeight - height) / 2 + y;
    }
    SDL_Rect textureSpecs = {x, y, width, height};
    SDL_RenderCopyEx(mRenderer, texture->getTexture(), clip, &textureSpecs, angle, center, flip);
}
void Renderer::setTextureBlendMode(Texture* texture, SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture->getTexture(), blending);
}
void Renderer::setTextureColor(Texture* texture, Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture->getTexture(), red, green, blue);
}
void Renderer::setTextureTransparency(Texture* texture, Uint8 opacity) {
    SDL_SetTextureAlphaMod(texture->getTexture(), opacity);
}