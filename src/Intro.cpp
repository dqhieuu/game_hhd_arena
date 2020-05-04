#include "Intro.h"

#include "Locator.h"
#include "Renderer.h"

Intro::Intro(Game* gameInstance) {
    mSplashScreenOpacity = 0;
    mAccumulator = 0;
    gCurrentGame = gameInstance;
    mIsFadingIn = true;
    mSplashScreen = new Texture("assets/img/splashscreen.png");
    mIntroVoice = new SoundEffect("assets/se/introvoice.wav");
    Locator::getSoundEffectPlayer()->loadSoundEffect(*mIntroVoice);
    if(gCurrentGame->mGameSettings.isFullScreen) mAccumulator-=150;
}

Intro::~Intro() {
    delete mSplashScreen;
    delete mIntroVoice;
}

void Intro::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
            gCurrentGame->setState(MAIN_MENU);
        }
    }
}

void Intro::handleLogic(double) {
    mAccumulator++;
    if(mAccumulator == 20) Locator::getSoundEffectPlayer()->play(mIntroVoice->id, mIntroVoice->id);
    if(mAccumulator >= 0) {
        if (mIsFadingIn) {
            mSplashScreenOpacity += 5;
            if (mSplashScreenOpacity >= 255) {
                mSplashScreenOpacity = 255;
                mIsFadingIn = false;
            }
        } else {
            if (mAccumulator >= 180) {
                mSplashScreenOpacity -= 12;
                if (mSplashScreenOpacity <= 0) {
                    mSplashScreenOpacity = 0;
                    gCurrentGame->setState(MAIN_MENU);
                }
            }
        }
    }
}

void Intro::handleGraphics() {
    // Reset transparency
    gRenderer->setTextureTransparency(mSplashScreen, mSplashScreenOpacity);
    gRenderer->renderTexture(mSplashScreen, 0, 0, 100, 100, nullptr, PIN_LEFT, PIN_TOP, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
}
