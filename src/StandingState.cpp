#include "StandingState.h"

#include "Character.h"
#include "CharacterState.h"
#include "JumpingState.h"
#include "Locator.h"
#include "utils.h"

CharacterState* StandingState::handleInput(Character& character, SDL_Event* e) {
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonLeft) {
            character.mMoveDirectionX = LEFT;
            character.mFacingDirection = LEFT;
        } else if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRight) {
            character.mMoveDirectionX = RIGHT;
            character.mFacingDirection = RIGHT;
        }
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonJump) {
            character.mVelY = -character.JUMP_VELOCITY;
            --character.mJumpLeft;
            return new JumpingState();
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
CharacterState* StandingState::handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t) {
    if (character.mMoveDirectionX == LEFT || character.mMoveDirectionX == RIGHT) {
        double normalizedAccelaration = character.ACCELERATION;
        double normalizedVelX = character.mVelX;
        double normalizedMaxVelX = character.MAX_VEL_X;

        if (character.mMoveDirectionX == LEFT) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
            normalizedMaxVelX = -normalizedMaxVelX;
        }
        if (normalizedVelX < 0)
            normalizedAccelaration *= 2.0;
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

        if (character.mVelX > 0) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
        }
        normalizedAccelaration *= 1.5;
        character.mX += character.mVelX * t + normalizedAccelaration * t * t / 2.0;
        character.mVelX += normalizedAccelaration * t;
        if (normalizedVelX + normalizedAccelaration * t >= 0)
            character.mVelX = 0;
    }
    SDL_Rect* solidBoxChar = Locator::getRenderer()->getAbsolutePosition(character.getSprite()->getTexture(), character.getPosX()-5, character.getPosY()-5, character.getSprite()->getClip()->w+10, character.getSprite()->getClip()->h+10, PIN_LEFT, PIN_TOP, SIZE_IN_PIXELS, SIZE_IN_PIXELS);
    for (auto& hitBoxObj : *solidObjects) {
        if (checkCollision(*solidBoxChar, hitBoxObj)) {
            printf("Touched.\n");
            character.mVelY = 0;
            character.mJumpLeft = character.MAX_JUMP_COUNT;
            character.mY = hitBoxObj.y - character.mCurrentSprite->getClip()->h;
            return nullptr;
        }
    }

    return new JumpingState();
    //printf("vel (%f %f) pos (%f %f) ts (%f)\n", character.mVelX, character.mVelY, character.mX, character.mY, t);
}

void StandingState::handleGraphics(Character& character) {

}