#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Texture {
   public:
    Texture();
    Texture(std::string path);
    Texture(TTF_Font *font, std::string textureText, SDL_Color textColor);
    ~Texture();
    void free();
    int getWidth() { return mWidth; }
    int getHeight() { return mWidth; }
    SDL_Texture* getTexture() { return mTexture; }
    bool loadFromRenderedText(TTF_Font *font, std::string text, SDL_Color textColor);
    bool loadFromFile(std::string path);
    void attachCamera(SDL_Rect * camera) {
        if(camera) mCamera = camera;
    };

   private:
    SDL_Texture *mTexture;
    SDL_Rect *mCamera = nullptr;
    bool isRendered;

   protected:
    int mWidth, mHeight;
};

#endif