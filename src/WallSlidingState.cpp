#include "WallSlidingState.h"

#include "JumpingState.h"
#include "Locator.h"
#include "StandingState.h"
#include "utils.h"

CharacterState* WallSlidingState::handleInput(Character& character, SDL_Event* e) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    Uint8& controllerKeyPressed = e->cbutton.button;
    SDL_GameController* controller = character.gGameInstance->getController();
    if ((e->type == SDL_KEYDOWN && e->key.repeat == 0) || e->type == SDL_CONTROLLERBUTTONDOWN) {
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonLeft || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
            character.mMoveDirectionX = LEFT;
        } else if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRight || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
            character.mMoveDirectionX = RIGHT;
        } else if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonJump || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_A)) {
            Direction jumpDirection;
            if (character.mFacingDirection == LEFT)
                jumpDirection = LEFT;
            else
                jumpDirection = RIGHT;
            character.directionalJump(jumpDirection);
            return new JumpingState();
        }
    }
    if ((e->type == SDL_KEYUP && e->key.repeat == 0) || e->type == SDL_CONTROLLERBUTTONUP) {
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonLeft || e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRight || controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_LEFT || controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
            if (state[character.gGameInstance->mGameSettings.buttonLeft] || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
                character.mMoveDirectionX = LEFT;
            } else if (state[character.gGameInstance->mGameSettings.buttonRight] || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
                character.mMoveDirectionX = RIGHT;
            } else
                character.mMoveDirectionX = NONE;
        }
    }
    return nullptr;
}
CharacterState* WallSlidingState::handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    SDL_GameController* controller = character.gGameInstance->getController();
    if ((state[character.gGameInstance->mGameSettings.buttonLeft] || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) && character.mFacingDirection == LEFT) {
        character.mMoveDirectionX = LEFT;
        return new JumpingState();
    } else if ((state[character.gGameInstance->mGameSettings.buttonRight] || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))  && character.mFacingDirection == RIGHT) {
        character.mMoveDirectionX = RIGHT;
        return new JumpingState();
    }
    if(character.mCharacterSprites["wallslide"].size())
        character.mCurrentSprite = &character.mCharacterSprites["wallslide"][0];
    double slidingVelocity = character.GRAVITY * 0.035;
    double previousVelY = character.mVel.y;
    int charWidth = character.mWidth;
    int charHeight = character.mHeight;
    if (character.mVel.x != 0)
        character.mVel.x = 0;
    if (character.mVel.y > slidingVelocity)
        character.mVel.y = slidingVelocity;
    else 
        character.mVel.y += character.GRAVITY * t;
    character.mPos.y += character.mVel.y * t;
    SDL_Rect solidBoxChar = Locator::getRenderer()->getAbsolutePosition(character.getCurrentSprite()->getTexture(), character.getPosX()-1, character.getPosY(), charWidth+2, charHeight);
    bool isCollidingWall = false;
    SDL_Rect collisionResult;
    for (auto& hitBoxObj : *solidObjects) {
        if (getCollision(solidBoxChar, hitBoxObj, collisionResult)) {
            if (collisionResult.w <=2) {
                isCollidingWall = true;
            } else {
                if(previousVelY>0) {
                printf("Touched side->ground.\n");
                    character.mVel.y = 0;
                    character.mJumpLeft = character.MAX_JUMP_COUNT;
                    character.mPos.y = hitBoxObj.y - charHeight;
                    return new StandingState();
                } else {
                    character.mPos.y = hitBoxObj.y + hitBoxObj.h;
                }
            }
        }
    }
    if(isCollidingWall) return nullptr;

    return new JumpingState();
    //printf("vel (%f %f) pos (%f %f) ts (%f)\n", character.mVel.x, character.mVel.y, character.mPos.x, character.mY, t);
}

void WallSlidingState::handleGraphics(Character&) {
}