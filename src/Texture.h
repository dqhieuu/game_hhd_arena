#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Texture {
   public:
    Texture();
    Texture(std::string path);
    Texture(TTF_Font *font, std::string textureText, SDL_Color textColor, bool highQuality = false);
    ~Texture();
    int getWidth() { return mWidth; }
    int getHeight() { return mWidth; }
    SDL_Texture* getTexture() { return mTexture; }
    bool loadFromRenderedText(TTF_Font *font, std::string text, SDL_Color textColor, bool highQuality = false);
    bool loadFromFile(std::string path);

   private:
    SDL_Texture *mTexture;
    bool isRendered;

   protected:
    int mWidth, mHeight;
};

#endif