#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Texture.h"
#include "Locator.h"


Texture::Texture() {
    //Initialize
    mTexture = nullptr;
    mWidth = mHeight = 0;
}

Texture::Texture(std::string path) {
    loadFromFile(path);
}

Texture::~Texture() {
    //Deallocate
    free();
}


bool Texture::hasClick() {
    //Check if mouse is in button
    bool inside = true;
    if (!isRendered) return false;
    int x, y;
    SDL_GetMouseState(&x, &y);
    std::cout << x << " " << y << "\n";
    //Mouse is left of the button
  //  if (mX < x || mX > x + mWidth || mY < y || mY > y + mHeight) {
   //     inside = false;
  //  }

    //Mouse is outside button
    return inside;
}

bool Texture::loadFromFile(std::string path) {
    //Get rid of preexisting texture
    free();
    //The final texture
    SDL_Texture* newTexture = NULL;


    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(Locator::getRenderer()->getSDLRenderer(), loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool Texture::loadFromRenderedText(TTF_Font* font, std::string textureText, SDL_Color textColor) {
    //Get rid of preexisting texture
    free();


    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(Locator::getRenderer()->getSDLRenderer(), textSurface);
        if (mTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return mTexture != NULL;
}

void Texture::free() {
    //Free texture if it exists
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}
