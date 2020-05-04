#include "JumpingState.h"
#include "utils.h"
#include "Character.h"
#include "CharacterState.h"
#include "StandingState.h"
#include "Locator.h"

CharacterState* JumpingState::handleInput(Character& character, SDL_Event* e) {
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonLeft) {
            character.mMoveDirectionX = LEFT;
            character.mFacingDirection = LEFT;
        } else if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRight) {
            character.mMoveDirectionX = RIGHT;
            character.mFacingDirection = RIGHT;
        }
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonJump) {
            if (character.mJumpLeft > 0) {
                --character.mJumpLeft;
                character.mVelY = -character.JUMP_VELOCITY;

            }
        }
    } else if (e->type == SDL_KEYUP && e->key.repeat == 0) {
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonLeft || e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRight) {
            if (state[character.gGameInstance->mGameSettings.buttonLeft]) {
                character.mMoveDirectionX = LEFT;
                character.mFacingDirection = LEFT;
            } else if (state[character.gGameInstance->mGameSettings.buttonRight]) {
                character.mMoveDirectionX = RIGHT;
                character.mFacingDirection = RIGHT;
            } else
                character.mMoveDirectionX = NONE;
        }
    }
    return nullptr;
}

CharacterState* JumpingState::handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t) {
    if (character.mMoveDirectionX == LEFT || character.mMoveDirectionX == RIGHT) {
        double normalizedAccelaration = character.ACCELERATION;
        double normalizedVelX = character.mVelX;
        double normalizedMaxVelX = character.MAX_VEL_X;
        normalizedAccelaration *= 0.5;
        if (character.mMoveDirectionX == LEFT) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
            normalizedMaxVelX = -normalizedMaxVelX;
        }
        if (normalizedVelX < 0)
            normalizedAccelaration *= 1.5;
        if (normalizedVelX >= character.MAX_VEL_X) {
            character.mX += character.mVelX * t;
            character.mVelX = normalizedMaxVelX;
        } else {
            character.mX += character.mVelX * t + normalizedAccelaration * t * t / 2.0;
            character.mVelX += normalizedAccelaration * t;
            if (normalizedVelX >= character.MAX_VEL_X) character.mVelX = normalizedMaxVelX;
        }
    } else if (character.mMoveDirectionX == NONE && character.mVelX != 0) {
        double normalizedAccelaration = character.ACCELERATION;
        double normalizedVelX = character.mVelX;
        normalizedAccelaration *= 0.04;
        if (character.mVelX > 0) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
        }
        character.mX += character.mVelX * t + normalizedAccelaration * t * t / 2.0;
        character.mVelX += normalizedAccelaration * t;
        if (normalizedVelX + normalizedAccelaration * t >= 0)
            character.mVelX = 0;
    }

    character.mY += character.mVelY*t;
    character.mVelY += character.GRAVITY*t;

    SDL_Rect* solidBoxChar = Locator::getRenderer()->getAbsolutePosition(character.getSprite()->getTexture(), character.getPosX(), character.getPosY(), character.getSprite()->getClip()->w, character.getSprite()->getClip()->h, PIN_LEFT, PIN_TOP, SIZE_IN_PIXELS, SIZE_IN_PIXELS);
    for (auto& hitBoxObj : *solidObjects) {
        if (checkCollision(*solidBoxChar, hitBoxObj)) {
            printf("Touched.\n");
            character.mVelY = 0;
            character.mJumpLeft = character.MAX_JUMP_COUNT;
            character.mY = hitBoxObj.y - character.mCurrentSprite->getClip()->h+1;
            return new StandingState();
        }
    }
    return nullptr;
}

void JumpingState::handleGraphics(Character& character) {}