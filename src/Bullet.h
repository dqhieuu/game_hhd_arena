#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

#include "GameState.h"
#include "Locator.h"
#include "Sprite.h"
#include "Timer.h"
#include "Vector2D.h"
#include <cmath>
#include <iostream>

class Bullet {
   public:
    Bullet(int x, int y);
    virtual ~Bullet(){};
    virtual void start();
    virtual bool isActive() { return mIsActive; }
    virtual bool exists() { return !mIsDestroyed; }
    virtual void destroy();
    virtual SDL_Rect* getHurtbox() = 0;
    virtual int getHPLoss() = 0;
    virtual void handleLogic(double t) = 0;
    virtual void handleGraphics() = 0;

   protected:
    Vector2D mPos;
    double mRotationDeg;
    Timer mTimer;
    bool mIsActive;
    bool mIsDestroyed;
};

class LinearBullet : public Bullet {
   public:
    LinearBullet(GameState& currentState, Sprite* bulletSprite, int x, int y, int width, int height, double velocity, int HPLoss, double rotationDeg = 0, double spinVelocity = 0, double lifeDistance = -1, bool fixMirror= false) : Bullet(x, y) {
        mVel.x = velocity;
        mVel.y = 0;
        mWidth = width;
        mHeight = height;
        mLifeDistance = lifeDistance;
        mDistanceTraveled = 0;
        mVel = mVel.rotate(rotationDeg);
        mCurrentDeg = rotationDeg;
        mSpinVelocity = spinVelocity;
        mBoundX = currentState.getWidth() + 500;
        mBoundY = currentState.getHeight() + 500;
        mBulletSprite = bulletSprite;
        mHPLoss = HPLoss;
        mFixMirror = fixMirror;
      //  printf("New bullet created (x:%d y:%d deg:%f)\n", x, y, rotationDeg);
    }
    ~LinearBullet(){
       // printf("Linear bullet destroyed\n");
    };
    virtual SDL_Rect* getHurtbox() {
        return &mCurrentHitbox;
    }

    virtual void handleLogic(double t) {
        if (!mIsDestroyed && mIsActive) {
            mPos+=mVel*t;
            mDistanceTraveled += mVel.length()*t;
            mRenderDest = {static_cast<int>(mPos.x), static_cast<int>(mPos.y), mWidth, mHeight};
            if (mSpinVelocity != 0) mCurrentDeg = fmod(mCurrentDeg + mSpinVelocity * t, 360.0);
            mCurrentHitbox = mBulletSprite->getProportionalHitboxes()[0].getMultipliedRect(mRenderDest);
            if (mPos.x <= -500 || mPos.y <= -500 || mPos.x >= mBoundX || mPos.y >= mBoundY || (mLifeDistance >= 0 && mDistanceTraveled > mLifeDistance)) {
                destroy();
            }
        }
    }

    virtual void handleGraphics() {
        if (!mIsDestroyed && mIsActive) {
            SDL_RendererFlip flipType = SDL_FLIP_NONE;
            if(mFixMirror && mCurrentDeg == 180.0) flipType = SDL_FLIP_VERTICAL;
            Locator::getRenderer()->renderTexture(mBulletSprite->getTexture(), mBulletSprite->getClip(), &mRenderDest, flipType, mCurrentDeg);
            Locator::getRenderer()->renderRect(&mCurrentHitbox, 255, 0, 0);
        }
    }

    virtual int getHPLoss() {
        return mHPLoss;
    }

   private:
    Vector2D mVel;
    int mBoundX;
    int mBoundY;
    int mWidth;
    int mHeight;
    int mHPLoss;
    double mDistanceTraveled;
    double mLifeDistance;
    double mSpinVelocity;
    double mCurrentDeg;
    Sprite* mBulletSprite;
    SDL_Rect mCurrentHitbox;
    SDL_Rect mRenderDest;
    bool mFixMirror;
};

class BeamBullet : public Bullet {
   public:
    BeamBullet(GameState&, int x, int y = 0, int width = 100, int height = 10000, int HPLoss = 10, int time = 500) : Bullet(x, y) {
        mPos.x = x;
        mPos.y = y;
        mWidth = width;
        mHeight = height;
        mLifeTime = time;
        mCurrentHitbox = {static_cast<int>(mPos.x), static_cast<int>(mPos.y), mWidth, mHeight};
        mHPLoss = HPLoss;
     //   printf("New beam bullet created (x:%d y:%d w:%d h:%d)\n", x, y, width, height);
    }
    ~BeamBullet(){
   //     printf("Beam bullet destroyed\n");
    };
    virtual SDL_Rect* getHurtbox() {
        return &mCurrentHitbox;
    }

    virtual void handleLogic(double) {
        if (!mIsDestroyed && mIsActive) {
            if (mTimer.getTicks() >= static_cast<Uint32>(mLifeTime)) {
                destroy();
            }
        }
    }

    virtual void handleGraphics() {
        if (!mIsDestroyed && mIsActive) {
            Locator::getRenderer()->renderRect(&mCurrentHitbox, 255, 0, 0);
        }
    }

    virtual int getHPLoss() {
        return mHPLoss;
    }

   private:
    int mWidth;
    int mHeight;
    int mHPLoss;
    int mLifeTime;
    SDL_Rect mCurrentHitbox;
    Timer bulletTimer;
};

#endif