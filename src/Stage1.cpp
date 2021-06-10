#include "Stage1.h"

#include "Character.h"
#include "Game.h"
#include "GameState.h"
#include "Locator.h"
#include "Texture.h"
#include "utils.h"
#include <algorithm>
#include <random>
#include <chrono>

Stage1::Stage1(Game* gameInstance, int stageWidth, int stageHeight, std::string character) {
    mWidth = stageWidth;
    mHeight = stageHeight;
    gCurrentGame = gameInstance;
    mSheet.loadFromFile(std::string("assets/img/objectsheet.PNG"));
    mSheet2.loadFromFile(std::string("assets/img/stage1objects.PNG"));
    mBackground.loadFromFile(std::string("assets/img/khabankbar2.png"));
    mSolidPlatform = new Sprite(&mSheet, 29, 23, 38, 42, true);
    mWideLight1.setSprite(&mSheet2, 8, 3, 88, 35);
    mWideLight1RotationPoint = {15, 16};
    mWideLight2.setSprite(&mSheet2, 197, 4, 86, 34);
    mWideLight2RotationPoint = {15, 16};
    mLaser.setSprite(&mSheet2, 8,41,99,1);
    mLaserRotationPoint = {1, 0};
    mCrowd1[0].setSprite(&mSheet2, 8, 3, 88, 35);
    mCrowd1[1].setSprite(&mSheet2, 8, 3, 88, 35);
    mCrowd2[0].setSprite(&mSheet2, 8, 3, 88, 35);
    mCrowd2[1].setSprite(&mSheet2, 8, 3, 88, 35);
    mCrowd3[0].setSprite(&mSheet2, 8, 3, 88, 35);
    mCrowd3[1].setSprite(&mSheet2, 8, 3, 88, 35);
    mBoss = new Character(gCurrentGame, this, 1100,450, "KhaBanh");
    mBoss->overrideBossState();
    mPlayer = new Character(gCurrentGame, this, 250, 350, character);
    mBossHealthBarBG.setSprite(&mSheet, 8,177,641,65);
    mBossRedHealthBar.setSprite(&mSheet, 486, 28, 66, 12);
    pos1 = gRenderer->getAbsolutePosition(mSolidPlatform->getTexture(), 0, 0, 2, 100, PIN_LEFT, PIN_TOP, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    pos2 = gRenderer->getAbsolutePosition(mSolidPlatform->getTexture(), 0, 0, 2, 100, PIN_RIGHT, PIN_TOP, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    pos3 = gRenderer->getAbsolutePosition(mSolidPlatform->getTexture(), 0, 0, 100, 5, PIN_LEFT, PIN_TOP, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    pos4 = gRenderer->getAbsolutePosition(mSolidPlatform->getTexture(), 0, 0, 100, 12, PIN_LEFT, PIN_BOTTOM, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    pos5 = gRenderer->getAbsolutePosition(mSolidPlatform->getTexture(), 200, 300, 11, 8, PIN_LEFT, PIN_TOP, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    pos6 = gRenderer->getAbsolutePosition(mSolidPlatform->getTexture(), 200, 300, 11, 8, PIN_RIGHT, PIN_TOP, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    mBulletSprite = new Sprite(&mSheet, 99, 34, 94, 34, false);
    mBulletSprite->addProportionalHitbox(0.25, 0.25, 0.5, 0.5);
    Locator::getMusicPlayer()->load("assets/bgm/stage1-bg.mp3");
    Locator::getSoundEffectPlayer()->loadSoundEffect("youdied", "assets/se/youdied.wav");
    Locator::getMusicPlayer()->play();
    Locator::getMusicPlayer()->setInternalVolume(50);
    mGameStateTimer.start();
    mDeathSheet.loadFromFile(std::string("assets/img/deathsheet.png"));
    mDeathText.setSprite(&mDeathSheet, 22,6, 546, 90);
    mDeathDimBG.setSprite(&mDeathSheet, 22,375,47,21);
    mDeathUnderlay.setSprite(&mDeathSheet, 22,102, 409, 263);
}
Stage1::~Stage1() {
    delete mPlayer;
}

void Stage1::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP || event->type == SDL_CONTROLLERBUTTONDOWN || event->type == SDL_CONTROLLERBUTTONUP) {
            if(event->key.keysym.scancode == SDL_SCANCODE_ESCAPE || (event->type == SDL_CONTROLLERBUTTONDOWN && event->cbutton.button == SDL_CONTROLLER_BUTTON_BACK)) {
                gCurrentGame->setState(MAIN_MENU);
            } else if(mPlayer->mHitPoints>0)
                mPlayer->handleEvent(event);
        }
            
    }
}

void processDeg(double& deg, const double& vel, char& isPositive,  const double& t) {
    if(isPositive) {
        if(deg>=150) {
            isPositive=0;
            deg=150;
        } else {
            deg+=vel*t;
        }
    } else {
        if(deg<=30) {
            isPositive=1;
            deg=30;
        } else {
            deg-=vel*t;
        }
    }
}

void Stage1::handleLogic(double timeStep) {
    if(mPlayer->mHitPoints<=0) {
        if(!hasStartedLoseState) {
            SDL_Haptic* controllerHaptic = gCurrentGame->mControllerHaptic;
            if(controllerHaptic!=nullptr) SDL_HapticRumblePlay(controllerHaptic, 1.0, 1500);
            Locator::getMusicPlayer()->stop();
            Locator::getSoundEffectPlayer()->stop();
            Locator::getSoundEffectPlayer()->play("youdied");
            hasStartedLoseState = true;
            mGameStateTimer.start();
        } else {
            if(mGameStateTimer.getTicks() > 7000) {
                gCurrentGame->setState(MAIN_MENU);
            } else {
                mDeathScreenOpacity = mGameStateTimer.getTicks()/8;
                if (mDeathScreenOpacity >= 255)
                    mDeathScreenOpacity = 255;
            }
        }
    } else if (mBoss->mHitPoints<=0) {
        if(!hasStartedWinState) {
        mTotalFightTime = static_cast<int>(mGameStateTimer.getTicks());
        hasStartedWinState = true;
        mGameStateTimer.start();
        } else {
            if(mGameStateTimer.getTicks() > 500) {
                std::string fightResult = std::to_string(mTotalFightTime) + " " + std::to_string(mPlayer->mHitPoints*100/mPlayer->MAX_HP);
                gCurrentGame->setState(STAGE_RESULT, fightResult);
            }
        }

    } else {
        mBoss->setEnemyPos(mPlayer->mPos);
        mPlayer->transferBullet(mPlayerBullets);
        mBoss->transferBullet(mEnemyBullets);
        mEnemyBullets.erase(std::remove_if(mEnemyBullets.begin(), mEnemyBullets.end(),[](const std::unique_ptr<Bullet>& bullet) { 
            return !(bullet->exists());
        }), mEnemyBullets.end());
        mPlayerBullets.erase(std::remove_if(mPlayerBullets.begin(), mPlayerBullets.end(),[](const std::unique_ptr<Bullet>& bullet) { 
            return !(bullet->exists());
        }), mPlayerBullets.end());

        SDL_Rect charPos = {mPlayer->getPosX(), mPlayer->getPosY(), mPlayer->mWidth, mPlayer->mHeight};
        for(auto & bullet:mEnemyBullets) {
            if(bullet->isActive()) {
                bullet->handleLogic(timeStep);
                if(checkCollision(charPos, *bullet->getHurtbox()) && !mPlayer->mCharInvincibleTimer.isStarted()) {
                    mPlayer->decreaseHP(bullet->getHPLoss());
                    bullet->destroy();
                }
            }
        }
        SDL_Rect bossPos = {mBoss->getPosX(), mBoss->getPosY(), mBoss->mWidth, mBoss->mHeight};
        for(auto & bullet:mPlayerBullets) {
            if(bullet->isActive()) {
                bullet->handleLogic(timeStep);
                if(checkCollision(bossPos, *bullet->getHurtbox())) {
                    mBoss->decreaseHP(bullet->getHPLoss());
                    bullet->destroy();
                }
            }
        }

        mSolidObjects.emplace_back(pos1);
        mSolidObjects.emplace_back(pos2);
        mSolidObjects.emplace_back(pos3);
        mSolidObjects.emplace_back(pos4);
        mSolidObjects.emplace_back(pos5);
        mSolidObjects.emplace_back(pos6);
        mPlayer->handleLogic(&mSolidObjects, timeStep);
        mBoss->handleLogic(&mSolidObjects,timeStep);
        mSolidObjects.clear();

        for(size_t i=0;i<mLVel.size();++i) {
            processDeg(mLDeg[i], mLVel[i], mLPositiveDir[i], timeStep);
        }
    }
}



void Stage1::handleGraphics() {
    gRenderer->renderTexture(&mBackground);
    SDL_Rect lpos1{400,-200, 1300,300};
    SDL_Rect lpos2{1100,-200, 1300,300};
    SDL_Rect lpos3{750,-200, 1300,300};
    gRenderer->setTextureColor(mWideLight1.getTexture(), 255,0,0);
    gRenderer->renderTexture(mWideLight1.getTexture(), mWideLight1.getClip(), &lpos1,SDL_FLIP_NONE, mLDeg[0], &mWideLight1RotationPoint);
    gRenderer->setTextureColor(mWideLight1.getTexture(), 255, 238, 0);
    gRenderer->renderTexture(mWideLight1.getTexture(), mWideLight1.getClip(), &lpos1,SDL_FLIP_NONE, mLDeg[1], &mWideLight1RotationPoint);
    gRenderer->setTextureColor(mWideLight1.getTexture(), 55, 255, 0);
    gRenderer->renderTexture(mWideLight1.getTexture(), mWideLight1.getClip(), &lpos2,SDL_FLIP_NONE, mLDeg[2], &mWideLight1RotationPoint);
    gRenderer->setTextureColor(mWideLight1.getTexture(), 21, 0, 255);
    gRenderer->renderTexture(mWideLight1.getTexture(), mWideLight1.getClip(), &lpos2,SDL_FLIP_NONE, mLDeg[3], &mWideLight1RotationPoint);
    gRenderer->setTextureColor(mWideLight1.getTexture(), 255,255,255);
    gRenderer->renderTexture(mWideLight1.getTexture(), mWideLight1.getClip(), &lpos3,SDL_FLIP_NONE, mLDeg[4], &mWideLight1RotationPoint);
    gRenderer->setTextureColor(mWideLight1.getTexture(), 189, 235, 52);
    gRenderer->renderTexture(mWideLight1.getTexture(), mWideLight1.getClip(), &lpos3,SDL_FLIP_NONE, mLDeg[5], &mWideLight1RotationPoint);
    gRenderer->setTextureColor(mWideLight1.getTexture(), 237, 52, 135);
//    gRenderer->renderTexture(mSolidPlatform->getTexture(), mSolidPlatform->getClip(), &pos2);
//    gRenderer->renderTexture(mSolidPlatform->getTexture(), mSolidPlatform->getClip(), &pos3);
//    gRenderer->renderTexture(mSolidPlatform->getTexture(), mSolidPlatform->getClip(), &pos4);
    gRenderer->renderTexture(mSolidPlatform->getTexture(), mSolidPlatform->getClip(), &pos5);
    gRenderer->renderTexture(mSolidPlatform->getTexture(), mSolidPlatform->getClip(), &pos6);
    for(auto & bullet:mEnemyBullets) {
        bullet->handleGraphics();
    }
    for(auto & bullet:mPlayerBullets) {
        bullet->handleGraphics();
    }

    Texture HPText(mPlayer->mCharFont, "HP", {0,0,0,255});
    Texture HPNumber(mPlayer->mCharFont, std::to_string(mPlayer->mHitPoints), {0,0,0,255});
    SDL_Rect posHPBarBG = {50,40, 288, 33};
    Locator::getRenderer()->renderTexture(mPlayer->mCharacterSprites["healthbg"][0].getTexture(), mPlayer->mCharacterSprites["healthbg"][0].getClip(), &posHPBarBG);
    SDL_Rect clipPosHPRedBar = *mPlayer->mCharacterSprites["healthbar"][0].getClip();
    clipPosHPRedBar.y-=mPlayer->mCharTimer.getTicks()/100%12;
    SDL_Rect posHPRedBar = {87,49, 200*(mPlayer->mHitPoints<0? 0:mPlayer->mHitPoints)/mPlayer->MAX_HP, 12};
    Locator::getRenderer()->renderTexture(mPlayer->mCharacterSprites["healthbar"][0].getTexture(), &clipPosHPRedBar, &posHPRedBar);
    SDL_Rect posHPText = Locator::getRenderer()->getAbsolutePosition(&HPText, 62, 42, -1, 20);
    Locator::getRenderer()->renderTexture(&HPText, nullptr, &posHPText);
    SDL_Rect posHPNumber = Locator::getRenderer()->getAbsolutePosition(&HPNumber, 290, 42, -1, 20);
    Locator::getRenderer()->renderTexture(&HPNumber, nullptr, &posHPNumber);

    mPlayer->handleGraphics();
    mBoss->handleGraphics();
    SDL_Rect posBossHPBar = Locator::getRenderer()->getAbsolutePosition(mBossHealthBarBG.getTexture(), 50,5,90,10, PIN_LEFT,PIN_BOTTOM, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
    Locator::getRenderer()->renderTexture(mBossHealthBarBG.getTexture(), mBossHealthBarBG.getClip(), &posBossHPBar);
    SDL_Rect posBossHPRedBar = {86,683,1107*(mBoss->mHitPoints<0? 0:mBoss->mHitPoints)/mBoss->MAX_HP,12};
    Locator::getRenderer()->renderTexture(mBossRedHealthBar.getTexture(), mBossRedHealthBar.getClip(), &posBossHPRedBar);


    if(mPlayer->mHitPoints<=0) {
        gRenderer->setTextureTransparency(mDeathDimBG.getTexture(), mDeathScreenOpacity);
        SDL_Rect posDeathDimBG = {-500,-300, 5000,3000};
        gRenderer->renderTexture(mDeathDimBG.getTexture(), mDeathDimBG.getClip(), &posDeathDimBG);
        gRenderer->setTextureTransparency(mDeathUnderlay.getTexture(), mDeathScreenOpacity);
        SDL_Rect posUnderLay = Locator::getRenderer()->getAbsolutePosition(mDeathUnderlay.getTexture(), 0, 0, 100, 50, PIN_CENTER, PIN_CENTER, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
        gRenderer->renderTexture(mDeathUnderlay.getTexture(), mDeathUnderlay.getClip(),&posUnderLay);
        gRenderer->setTextureTransparency(mDeathText.getTexture(), mDeathScreenOpacity);
        SDL_Rect posText = Locator::getRenderer()->getAbsolutePosition(mDeathUnderlay.getTexture(), 0, 0, 70, 20, PIN_CENTER, PIN_CENTER, SIZE_IN_PERCENTAGE, SIZE_IN_PERCENTAGE);
        gRenderer->renderTexture(mDeathText.getTexture(), mDeathText.getClip(), &posText);

    }
}
