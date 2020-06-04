#include "StageResult.h"

#include <SDL_ttf.h>

#include <sstream>

#include "Renderer.h"

StageResult::StageResult(Game* gameInstance, std::string playerStats) {
    std::stringstream statsStream;
    std::string temp;
    statsStream << playerStats;
    statsStream >> temp;
    mWinTime = std::stoi(temp);
    statsStream >> temp;
    mHPPercentage = std::stoi(temp);

    gCurrentGame = gameInstance;
    mGameStateTimer.start();
    mFont1 = TTF_OpenFont("assets/fonts/HLT BicKhamScriptPro_Regular.ttf", 50);
    mFont2 = TTF_OpenFont("assets/fonts/HLT BicKhamScriptPro_Regular.ttf", 64);
    SDL_Color grayishBlack = {22, 22, 22, 255};
    mTimeLabel.loadFromRenderedText(mFont1, "Thời gian:", grayishBlack, true);

    SDL_Color crimson = {129, 0, 0, 255};
    int minute = mWinTime / 60000;
    int second = mWinTime / 1000 % 60;
    std::string timeCount = std::to_string(minute) + "'" + std::to_string(second) + "s";
    mTimeText.loadFromRenderedText(mFont2, timeCount, crimson, true);

    mScoreLabel.loadFromRenderedText(mFont1, "Điểm:", grayishBlack, true);

    mScore = static_cast<int>(150000.0 * (1.0 - static_cast<double>(mWinTime) / (mWinTime + 100000.0)) + 30000.0 * mHPPercentage / 100);

    mRankLabel.loadFromRenderedText(mFont2, "Xếp hạng", grayishBlack, true);

    mRankS.setSprite(&mObjectSheet,63, 935, 60,89);
    mRankA.setSprite(&mObjectSheet,155,935,88,87);
    mRankB.setSprite(&mObjectSheet,274,936,70,87);
    mRankC.setSprite(&mObjectSheet,383,935,73,89);
    mRankD.setSprite(&mObjectSheet,491,936,83,86);
    if(mScore>=115000) mCurrentRank = &mRankS;
    else if(mScore>=100000) mCurrentRank = &mRankA;
    else if(mScore>=90000) mCurrentRank = &mRankB;
    else if(mScore>=85000) mCurrentRank = &mRankC;
    else mCurrentRank = &mRankD;

    mBackgroundTexture.loadFromFile("assets/img/not-main-menu-bg.png");
    mObjectSheet.loadFromFile("assets/img/objectsheet.png");
    mParchmentBG.setSprite(&mObjectSheet, 10, 418, 384, 484);
    for (int i = 0; i < 8; ++i)
        mBackground.push_back(Sprite(&mBackgroundTexture, 0, 282 * i, 500, 282));
}
StageResult::~StageResult() {
    TTF_CloseFont(mFont1);
    TTF_CloseFont(mFont2);
}

void StageResult::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if ((event->type == SDL_KEYDOWN && event->key.repeat == 0) || (event->type == SDL_CONTROLLERBUTTONDOWN)) {
            SDL_Scancode& keyPressed = event->key.keysym.scancode;
            Uint8& controllerKeyPressed = event->cbutton.button;
            if (keyPressed == SDL_SCANCODE_RETURN || keyPressed == SDL_SCANCODE_SPACE || keyPressed == gCurrentGame->mGameSettings.buttonJump || (event->type == SDL_CONTROLLERBUTTONDOWN && (controllerKeyPressed == SDL_CONTROLLER_BUTTON_A || controllerKeyPressed == SDL_CONTROLLER_BUTTON_START))) {
                if (mGameStateTimer.getTicks() > 5000) {
                    gCurrentGame->setState(MAIN_MENU);
                }
            }
        }
    }
}

void StageResult::handleLogic(double) {
    Uint32 currentTick = mGameStateTimer.getTicks();
    if(currentTick>=1000)
        mRenderScore = static_cast<double>(currentTick-1000) / 2000.0 * mScore;
    if (currentTick >= 3000)
        mRenderScore = mScore;
}

void StageResult::handleGraphics() {
    SDL_Color crimson = {129, 0, 0, 255};
    Uint32 currentTick = mGameStateTimer.getTicks();
    Sprite* currentBG = &mBackground[mGameStateTimer.getTicks() / 100 % 8];
    gRenderer->renderTexture(currentBG->getTexture(), currentBG->getClip());
    SDL_Rect posParchmentBG = gRenderer->getAbsolutePosition(mParchmentBG.getTexture(), 0, 0, 40, 80, PIN_CENTER, PIN_CENTER, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    gRenderer->renderTexture(mParchmentBG.getTexture(), mParchmentBG.getClip(), &posParchmentBG);
    if (currentTick >= 500) {
        SDL_Rect posTimeLabel = gRenderer->getAbsolutePosition(&mTimeLabel, 500, -150, -1, 65, PIN_LEFT, PIN_CENTER);
        gRenderer->renderTexture(&mTimeLabel, nullptr, &posTimeLabel);

        SDL_Rect posTimeText = gRenderer->getAbsolutePosition(&mTimeText, 650, -155, -1, 75, PIN_LEFT, PIN_CENTER);
        gRenderer->renderTexture(&mTimeText, nullptr, &posTimeText);
    }

    if (currentTick >= 1000) {
        SDL_Rect posScoreLabel = gRenderer->getAbsolutePosition(&mScoreLabel, 500, -50, -1, 65, PIN_LEFT, PIN_CENTER);
        gRenderer->renderTexture(&mScoreLabel, nullptr, &posScoreLabel);

        Texture scoreText(mFont2, std::to_string(mRenderScore), crimson, true);
        SDL_Rect posScoreText = gRenderer->getAbsolutePosition(&scoreText, 600, -55, -1, 75, PIN_LEFT, PIN_CENTER);
        gRenderer->renderTexture(&scoreText, nullptr, &posScoreText);
    }
    if (currentTick >= 3500) {
        SDL_Rect posRankLabel = gRenderer->getAbsolutePosition(&mRankLabel, 0, 20, -1, 75, PIN_CENTER, PIN_CENTER);
        gRenderer->renderTexture(&mRankLabel, nullptr, &posRankLabel);
    }
    if (currentTick >= 4000) {
        SDL_Rect posRankMark = gRenderer->getAbsolutePosition(mCurrentRank->getTexture(), 0, 120, 100, 120, PIN_CENTER, PIN_CENTER);
        gRenderer->renderTexture(mCurrentRank->getTexture(), mCurrentRank->getClip(), &posRankMark);
    }
}
