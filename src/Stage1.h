#ifndef STAGE_1_H
#define STAGE_1_H

#include "IRenderer.h"
#include "Texture.h"
#include "Character.h"
#include "Game.h"
#include "Locator.h"
#include "GameState.h"
#include <vector>

class Stage1 : public GameState {
   public:
    Stage1(Game* gameInstance);
    ~Stage1();
    void handleEvents(SDL_Event* event);
    void handleLogic(double timeStep);
    void handleGraphics();
   private:
    IRenderer* gRenderer = Locator::getRenderer();
    std::vector<SDL_Rect> mSolidObjects;
    std::vector<Sprite> mHurtObjects;

    Texture* mBackground;
    Texture* mPlatform;
    Character* mPlayer;
    Game* gCurrentGame;
};

#endif