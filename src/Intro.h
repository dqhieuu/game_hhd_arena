#ifndef INTRO_H
#define INTRO_H

#include "Texture.h"
#include "Game.h"
#include "Locator.h"
#include "SoundEffect.h"
#include <vector>

class Intro : public GameState {
   public:
    Intro(Game* gameInstance);
    ~Intro();
    void handleEvents(SDL_Event* event);
    void handleLogic(double timeStep);
    void handleGraphics();
   private:
    IRenderer* gRenderer = Locator::getRenderer();
    Texture* mSplashScreen;
    SoundEffect* mIntroVoice;
    Game* gCurrentGame;
    int mAccumulator;
    int mSplashScreenOpacity;
    bool mIsFadingIn;
};

#endif