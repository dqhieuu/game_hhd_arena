#include "GameState.h"
#include "Stage1.h"
#include "Texture.h"
#include "Game.h"
#include "Character.h"
#include "Locator.h"

Stage1::Stage1(Game* gameInstance) {
    gCurrentGame = gameInstance;
    mBackground = new Texture(std::string("assets/img/do-pixel-art-environment-background.jpg"));
    mPlatform = new Texture(std::string("assets/img/platform-png-6.png"));
    mPlayer = new Character(0, 150);
    Locator::getMusicPlayer()->load("assets/bgm/MusMus-BGM-106.mp3");
    Locator::getMusicPlayer()->play();
    Locator::getMusicPlayer()->setVolume(50);
}
Stage1::~Stage1() {
    delete mBackground;
    delete mPlayer;
}
void Stage1::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
            mPlayer->handleEvent(event);
    }
}
void Stage1::handleLogic(double timeStep) {
    mPlayer->move(timeStep);
}
void Stage1::render() {
    gRenderer->renderTexture(mBackground, 0, 0,100,100,nullptr,PIN_LEFT,PIN_TOP,SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    gRenderer->renderTexture(mPlatform, 0, 0,100,30,nullptr,PIN_LEFT,PIN_BOTTOM,SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    mPlayer->handleGraphics();
}
