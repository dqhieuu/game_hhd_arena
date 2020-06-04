#ifndef STAGE_RESULT_H
#define STAGE_RESULT_H

#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Locator.h"
#include "SoundEffect.h"
#include <vector>

class StageResult : public GameState {
   public:
    StageResult(Game* gameInstance, std::string playerStats);
    ~StageResult();
    void handleEvents(SDL_Event* event);
    void handleLogic(double timeStep);
    void handleGraphics();
   private:
    const int NUM_OF_OPTIONS = 3;
    IRenderer* gRenderer = Locator::getRenderer();
    int mChoosingOption;
    Texture mObjectSheet;
    TTF_Font* mFont1;
    TTF_Font* mFont2;
    Texture mBackgroundTexture;
    Texture mScoreLabel;
    Texture mTimeLabel;
    Texture mTimeText;
    Texture mRankLabel;
    Sprite mParchmentBG;
    Sprite mRankS;
    Sprite mRankA;
    Sprite mRankB;
    Sprite mRankC;
    Sprite mRankD;
    Sprite* mCurrentRank;
    std::vector<Sprite> mBackground;
    Game* gCurrentGame;
    int mWinTime;
    int mHPPercentage;
    int mScore;
    int mRenderScore;
};

#endif