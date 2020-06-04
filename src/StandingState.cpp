#include "StandingState.h"

#include "Character.h"
#include "CharacterState.h"
#include "JumpingState.h"
#include "Locator.h"
#include "utils.h"


CharacterState* StandingState::handleInput(Character& character, SDL_Event* e) {
    Uint8& controllerKeyPressed = e->cbutton.button;
    SDL_GameController* controller = character.gGameInstance->getController();
    if ((e->type == SDL_KEYDOWN && e->key.repeat == 0) || e->type == SDL_CONTROLLERBUTTONDOWN) {
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonLeft || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
            character.mMoveDirectionX = LEFT;
            character.mFacingDirection = LEFT;
        } else if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRight || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
            character.mMoveDirectionX = RIGHT;
            character.mFacingDirection = RIGHT;
        }
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonJump || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_A)) {
            character.jump();
            return new JumpingState();
        }
    } else if ((e->type == SDL_KEYUP && e->key.repeat == 0) || e->type == SDL_CONTROLLERBUTTONUP) {
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonLeft || e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRight || controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_LEFT || controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
            if (state[character.gGameInstance->mGameSettings.buttonLeft] || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
                character.mMoveDirectionX = LEFT;
                character.mFacingDirection = LEFT;
            } else if (state[character.gGameInstance->mGameSettings.buttonRight] || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
                character.mMoveDirectionX = RIGHT;
                character.mFacingDirection = RIGHT;
            } else
                character.mMoveDirectionX = NONE;
        }
    }
    return nullptr;
}

CharacterState* StandingState::handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t) {
    if (character.mVel.x != 0) {
        character.mCurrentSprite = &character.mCharacterSprites["move"][mCharStateTimer.getTicks() / 200 % character.mCharacterSprites["move"].size()];
        if (mCharStateTimer.getTicks() / 100 % 2 == 0) {
            if(mRunSoundOn) {
                Locator::getSoundEffectPlayer()->play("step");
                mRunSoundOn = false;
            }
        } else {
            mRunSoundOn = true;
        }
    } else
        character.mCurrentSprite = &character.mCharacterSprites["stand"][mCharStateTimer.getTicks() / 200 % character.mCharacterSprites["stand"].size()];

    double previousVelX = character.mVel.x;
    int charWidth = character.mWidth;
    int charHeight = character.mHeight;
    character.move(t, false);
    SDL_Rect solidBoxChar = Locator::getRenderer()->getAbsolutePosition(character.getCurrentSprite()->getTexture(), character.getPosX(), character.getPosY(), charWidth, charHeight + 1);
    bool isOnPlatform = false;
    SDL_Rect collisionResult;
    for (auto& hitBoxObj : *solidObjects)
        if (getCollision(solidBoxChar, hitBoxObj, collisionResult)) {
            if (collisionResult.h <= 2)
                isOnPlatform = true;
            else {
                if (previousVelX < 0)
                    character.mPos.x = hitBoxObj.x + hitBoxObj.w;
                else if (previousVelX > 0)
                    character.mPos.x = hitBoxObj.x - charWidth;
            }
        }
           // printf("vel (%f %f) pos (%f %f) ts (%f)\n", character.mVel.x, character.mVel.y, character.mPos.x, character.mPos.y, t);
    if (isOnPlatform) return nullptr;
    return new JumpingState();
}

void StandingState::handleGraphics(Character&) {
}