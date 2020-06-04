#include "Intro.h"

#include "Locator.h"
#include "Renderer.h"

Intro::Intro(Game* gameInstance) {
    mGameStateTimer.start();
    mSplashScreenOpacity = 0;
    gCurrentGame = gameInstance;
    mHasPlayedVoice = false;
    mIsFadingIn = true;
    mSplashScreen = new Texture("assets/img/splashscreen.png");
    Locator::getSoundEffectPlayer()->loadSoundEffect("introvoice","assets/se/introvoice.wav");
}

Intro::~Intro() {
    delete mSplashScreen;
}

void Intro::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if ((event->type == SDL_KEYDOWN && event->key.repeat == 0) || event->type == SDL_CONTROLLERBUTTONDOWN) {
            gCurrentGame->setState(MAIN_MENU);
        }
    }
}

void Intro::handleLogic(double) {
    if(!mHasPlayedVoice && mGameStateTimer.getTicks()>=200) {
        Locator::getSoundEffectPlayer()->play("introvoice");
        mHasPlayedVoice = true;
    }
    if (mIsFadingIn) {
        mSplashScreenOpacity = mGameStateTimer.getTicks()/4;
        if (mSplashScreenOpacity >= 255) {
            mSplashScreenOpacity = 255;
            mIsFadingIn = false;
        }
    } else {
        if (mGameStateTimer.getTicks() >= 2000) {
            mSplashScreenOpacity = 255 - (mGameStateTimer.getTicks() - 2000)/4;
            if (mSplashScreenOpacity <= 0) {
                mSplashScreenOpacity = 0;
                gCurrentGame->setState(MAIN_MENU);
            }
        }
    }
}

void Intro::handleGraphics() {
    // Reset transparency
    gRenderer->setTextureTransparency(mSplashScreen, mSplashScreenOpacity);
    gRenderer->renderTexture(mSplashScreen);
}
