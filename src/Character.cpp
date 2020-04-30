#include "Character.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <cstdlib>
#include <string>
#include <vector>

#include "Sprite.h"
#include "Texture.h"
#include "SoundEffect.h"
#include "Locator.h"

Character::Character(int x, int y) {
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
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        if (e->key.keysym.scancode == SDL_SCANCODE_UP)
            mMoveDirectionY = UP;
        else if (e->key.keysym.scancode == SDL_SCANCODE_DOWN)
            mMoveDirectionY = DOWN;
        if (e->key.keysym.scancode == SDL_SCANCODE_LEFT) {
            mMoveDirectionX = LEFT;
            mFacingDirection = LEFT;
        }
        else if (e->key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            mMoveDirectionX = RIGHT;
            mFacingDirection = RIGHT;
        }
    } else if (e->type == SDL_KEYUP && e->key.repeat == 0) {
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (e->key.keysym.scancode == SDL_SCANCODE_UP || e->key.keysym.scancode == SDL_SCANCODE_DOWN) {
            if (state[SDL_SCANCODE_UP])
                mMoveDirectionY = UP;
            else if (state[SDL_SCANCODE_DOWN])
                mMoveDirectionY = DOWN;
            else
                mMoveDirectionY = NONE;
        }

        if (e->key.keysym.scancode == SDL_SCANCODE_LEFT || e->key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            if (state[SDL_SCANCODE_LEFT]) {
                mMoveDirectionX = LEFT;
                mFacingDirection = LEFT;
            }
            else if (state[SDL_SCANCODE_RIGHT]) {
                mMoveDirectionX = RIGHT;
                mFacingDirection = RIGHT;
            }
            else
                mMoveDirectionX = NONE;
        }
    }
}

void Character::move(double t) {
    if (mMoveDirectionX == LEFT) {
        if (mVelX > 0) {
            mX += mVelX * t + -ACCELERATION * t * t;
            mVelX += -2.0 * ACCELERATION * t;
        } else {
            mX += mVelX * t + -ACCELERATION * t * t / 2.0;
            mVelX += -ACCELERATION * t;
            if (mVelX <= -MAX_VEL_X) mVelX = -MAX_VEL_X;
        }
    } else if (mMoveDirectionX == RIGHT) {
        if (mVelX < 0) {
            mX += mVelX * t + ACCELERATION * t * t;
            mVelX += 2.0 * ACCELERATION * t;
        } else {
            mX += mVelX * t + ACCELERATION * t * t / 2.0;
            mVelX += ACCELERATION * t;
            if (mVelX >= MAX_VEL_X) mVelX = MAX_VEL_X;
        }
    } else if (mMoveDirectionX == NONE && mVelX != 0) {
        if (mVelX > 0) {
            mX += mVelX * t + -ACCELERATION * t * t;
            mVelX += -2.0 * ACCELERATION * t;
            if (mVelX <= 0)
                mVelX = 0;
        } else {
            mX += mVelX * t + ACCELERATION * t * t;
            mVelX += 2.0 * ACCELERATION * t;
            if (mVelX >= 0)
                mVelX = 0;
        }
    }

    if (mMoveDirectionY == UP) {
        if (mVelY - ACCELERATION >= -MAX_VEL_X) mVelY -= ACCELERATION;
    } else if (mMoveDirectionY == DOWN) {
        if (mVelY + ACCELERATION <= MAX_VEL_X) mVelY += ACCELERATION;
    } else if (mMoveDirectionY == NONE && mVelY != 0) {
        if (mVelY > 0) {
            if (mVelY <= 3.0 * ACCELERATION)
                mVelY = 0;
            else
                mVelY -= 2.0 * ACCELERATION;
        } else {
            if (mVelY >= -3.0 * ACCELERATION)
                mVelY = 0;
            else
                mVelY += 2.0 * ACCELERATION;
        }
    }
    printf("vel (%f %f) pos (%f %f) ts (%f)\n", mVelX, mVelY, mX, mY, t);
}

void Character::handleGraphics() {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (mFacingDirection == LEFT) flip = SDL_FLIP_HORIZONTAL;
    if (mAccumulator >= 90) mAccumulator=0;
    if (mVelX != 0) {
        mCurrentSprite = mMoveSprite[mAccumulator/15%3];
        if(mAccumulator%30 == 0) Locator::getSoundEffectPlayer()->play(mStep->id, mStep->id);
    } else mCurrentSprite= mMoveSprite[0];

    Locator::getRenderer()->renderTexture(getSprite()->getTexture(), getPosX(), getPosY(), getSprite()->getClip()->w, getSprite()->getClip()->h, getSprite()->getClip(),PIN_LEFT,PIN_BOTTOM,SIZE_IN_PIXELS,SIZE_IN_PIXELS,flip);
    ++mAccumulator;
}

void Character::update(double timeStep) {
    move(timeStep);
}