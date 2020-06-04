#include "JumpingState.h"

#include <memory>

#include "Locator.h"
#include "StandingState.h"
#include "WallSlidingState.h"
#include "utils.h"

CharacterState* JumpingState::handleInput(Character& character, SDL_Event* e) {
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
        }
    } else if ((e->type == SDL_KEYUP && e->key.repeat == 0) || e->type == SDL_CONTROLLERBUTTONUP) {
        const Uint8* state = SDL_GetKeyboardState(nullptr);
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

CharacterState* JumpingState::handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t) {
    if(character.mCharacterSprites["jump"].size())
        character.mCurrentSprite = &character.mCharacterSprites["jump"][mCharStateTimer.getTicks() / 100 % character.mCharacterSprites["jump"].size()];
    double previousVelX = character.mVel.x;
    double previousVelY = character.mVel.y;
    int charWidth = character.mWidth;
    int charHeight = character.mHeight;
    character.move(t, true);
    SDL_Rect solidBoxChar = Locator::getRenderer()->getAbsolutePosition(character.getCurrentSprite()->getTexture(), character.getPosX(), character.getPosY(), charWidth, charHeight);
    for (auto& hitBoxObj : *solidObjects) {
        if (checkCollision(solidBoxChar, hitBoxObj)) {
            printf("Touched air->side.\n");
            if (previousVelX < 0) {
                character.mPos.x = hitBoxObj.x + hitBoxObj.w;
                character.mFacingDirection = RIGHT;
            } else {
                character.mPos.x = hitBoxObj.x - charWidth;
                character.mFacingDirection = LEFT;
            }
            character.mVel.x = 0;
            character.mJumpLeft = 1;
            return new WallSlidingState(&character);
        }
    }
    character.mPos.y += character.mVel.y * t;
    character.mVel.y += character.GRAVITY * t;

    solidBoxChar.y = character.getPosY();

    for (auto& hitBoxObj : *solidObjects) {
        if (checkCollision(solidBoxChar, hitBoxObj)) {
            if (previousVelY > 0) {
                printf("Touched air->ground.\n");
                character.mVel.y = 0;
                character.mJumpLeft = character.MAX_JUMP_COUNT;
                character.mPos.y = hitBoxObj.y - charHeight;
                return new StandingState();
            } else {
                printf("Touched air->ceiling.\n");
                character.mPos.y = hitBoxObj.y + hitBoxObj.h;
                character.mVel.y = 0;
            }
        }
    }
    return nullptr;
}

void JumpingState::handleGraphics(Character&) {
}