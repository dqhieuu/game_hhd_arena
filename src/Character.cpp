#include "Character.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <cstdlib>
#include <string>
#include <vector>

#include "Locator.h"
#include "SoundEffect.h"
#include "Sprite.h"
#include "Texture.h"
#include "CharacterState.h"
#include "JumpingState.h"
#include "StandingState.h"

Character::Character(Game* gameInstance, int x, int y) {
    mVelX = mVelY = 0;
    mMoveDirectionX = mMoveDirectionY = NONE;
    mFacingDirection = RIGHT;
    mX = x;
    mY = y;
    mSpriteTexture = new Texture("assets/img/charsheet.png");
    mMoveSprite[0] = new Sprite(mSpriteTexture, 43, 5, 155, 240, true);
    mMoveSprite[1] = new Sprite(mSpriteTexture, 307, 5, 155, 240, true);
    mMoveSprite[2] = new Sprite(mSpriteTexture, 42, 262, 155, 240, true);
    mCurrentSprite = mMoveSprite[0];
    mStep = new SoundEffect("assets/se/wibu_dibo.wav");
    Locator::getSoundEffectPlayer()->loadSoundEffect(*mStep);
    mAccumulator = 0;
    mJumpLeft = MAX_JUMP_COUNT;
    gGameInstance = gameInstance;
    mCurrentState = new StandingState();
}

int Character::getPosX() {
    return static_cast<int>(mX);
}

int Character::getPosY() {
    return static_cast<int>(mY);
}

Sprite* Character::getSprite() {
    return mCurrentSprite;
}

void Character::handleEvent(SDL_Event* e) {
    CharacterState* newState = mCurrentState->handleInput(*this, e);
    if (newState != nullptr) {
        delete mCurrentState;
        mCurrentState = newState;
    }
}

void Character::handleLogic(std::vector<SDL_Rect>* solidObjects, double timeStep) {
    CharacterState* newState = mCurrentState->handleLogic(*this, solidObjects, timeStep);
    if (newState != nullptr) {
        delete mCurrentState;
        mCurrentState = newState;
    }
}

void Character::handleGraphics() {
    mCurrentState->handleGraphics(*this);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (mFacingDirection == LEFT) flip = SDL_FLIP_HORIZONTAL;
    if (mAccumulator >= 100000) mAccumulator = 0;
    if (mVelX != 0) {
        mCurrentSprite = mMoveSprite[mAccumulator / 15 % 3];
        if (mAccumulator % 30 == 0) Locator::getSoundEffectPlayer()->play(mStep->id, mStep->id);
    } else
        mCurrentSprite = mMoveSprite[0];

    Locator::getRenderer()->renderTexture(getSprite()->getTexture(), getPosX(), getPosY(), getSprite()->getClip()->w, getSprite()->getClip()->h, getSprite()->getClip(), PIN_LEFT, PIN_TOP, SIZE_IN_PIXELS, SIZE_IN_PIXELS, flip);
    ++mAccumulator;
}

void Character::move(double t) {
    if (mMoveDirectionX == LEFT || mMoveDirectionX == RIGHT) {
        double normalizedAccelaration = ACCELERATION;
        double normalizedVelX = mVelX;
        double normalizedMaxVelX = MAX_VEL_X;

        if (mMoveDirectionX == LEFT) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
            normalizedMaxVelX = -normalizedMaxVelX;
        }
        if (normalizedVelX < 0)
            normalizedAccelaration *= 2.0;
        if (normalizedVelX >= MAX_VEL_X) {
            mX += mVelX * t;
            mVelX = normalizedMaxVelX;
        } else {
            mX += mVelX * t + normalizedAccelaration * t * t / 2.0;
            mVelX += normalizedAccelaration * t;
            if (normalizedVelX >= MAX_VEL_X) mVelX = normalizedMaxVelX;
        }
    } else if (mMoveDirectionX == NONE && mVelX != 0) {
        double normalizedAccelaration = ACCELERATION;
        double normalizedVelX = mVelX;

        if (mVelX > 0) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
        }
        normalizedAccelaration *= 1.5;
        mX += mVelX * t + normalizedAccelaration * t * t / 2.0;
        mVelX += normalizedAccelaration * t;
        if (normalizedVelX + normalizedAccelaration * t >= 0)
            mVelX = 0;
    }
}