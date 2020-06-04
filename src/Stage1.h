#ifndef STAGE_1_H
#define STAGE_1_H

#include <vector>

#include "Character.h"
#include "Game.h"
#include "GameState.h"
#include "IRenderer.h"
#include "Locator.h"
#include "Sprite.h"
#include "Texture.h"
#include "Bullet.h"
#include <memory>
#include <string>
#include <array>

class Stage1 : public GameState {
   public:
    Stage1(Game* gameInstance, int stageWidth, int stageHeight, std::string character);
    ~Stage1();
    void handleEvents(SDL_Event* event);
    void handleLogic(double timeStep);
    void handleGraphics();

    void addEnemyBullet(Bullet* enemyBullet) {
        mEnemyBullets.push_back(std::unique_ptr<Bullet>(enemyBullet));
    }

    void addPlayerBullet(Bullet* enemyBullet) {
        mPlayerBullets.push_back(std::unique_ptr<Bullet>(enemyBullet));
    }


    std::vector<std::unique_ptr<Bullet>> mEnemyBullets;
    std::vector<std::unique_ptr<Bullet>> mPlayerBullets;
   private:
    IRenderer* gRenderer = Locator::getRenderer();
    std::vector<SDL_Rect> mSolidObjects;
    std::unordered_map<std::string, Texture> mSpriteSheets;
    SpriteDictionary mSprites;


    Texture mBackground;
    Texture mSheet;
    Texture mSheet2;
    Sprite* mSolidPlatform;
    Sprite mWideLight1;
    SDL_Point mWideLight1RotationPoint;
    Sprite mWideLight2;
    SDL_Point mWideLight2RotationPoint;
    Sprite mLaser;
    SDL_Point mLaserRotationPoint;
    Sprite mCrowd1[2];
    Sprite mCrowd2[2];
    Sprite mCrowd3[2];
    Sprite* mBulletSprite;
    SDL_Rect pos1;
    SDL_Rect pos2;
    SDL_Rect pos3;
    SDL_Rect pos4;
    SDL_Rect pos5, pos6, pos7, pos8;
    Character* mPlayer;
    Character* mBoss;
    Game* gCurrentGame;
    std::vector<double> mLDeg = {200,210,220,200,230,220};
    std::vector<double> mLVel = {70,80,90,85,60,80};
    std::vector<char> mLPositiveDir = {1,0,1,0,1,0};
    Texture mDeathSheet;
    Sprite mDeathText;
    Sprite mDeathUnderlay;
    Sprite mDeathDimBG;
    bool hasStartedLoseState = false;
    bool hasStartedWinState = false;
    int mDeathScreenOpacity = 0;
    int mTotalFightTime;
    Sprite mBossHealthBarBG;
    Sprite mBossRedHealthBar;
};

#endif