#include "DoNothingState.h"

#include "Locator.h"
#include "MeleeAttackingState.h"
#include "RangedAttackingState.h"

MeleeAttackingState::MeleeAttackingState(Character& character) {
    Locator::getSoundEffectPlayer()->play("melee");
    if(character.mFacingDirection == RIGHT) {
        if(character.mCharName == "Duong") {
            character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new BeamBullet(*character.gGameStateInstance, character.mPos.x+40, character.mPos.y-80, 120, 100, 60, 50)));
        } else {
            character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new BeamBullet(*character.gGameStateInstance, character.mPos.x+30, character.mPos.y-60, 90, 70, 80, 50)));
        }
    } else {
        if(character.mCharName == "Duong") {
            character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new BeamBullet(*character.gGameStateInstance, character.mPos.x-110, character.mPos.y-80, 120, 100, 60, 50)));
        } else {
            character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new BeamBullet(*character.gGameStateInstance, character.mPos.x-90, character.mPos.y-60, 90, 70, 80, 50)));
        }
    }
    character.mCharacterBullets.back()->start();
    mCharStateTimer.start();
    mActionDuration = 300;
    mStockedState = 0;
}

CharacterState* MeleeAttackingState::handleInput(Character& character, SDL_Event* e) {
    if ((e->type == SDL_KEYDOWN && e->key.repeat == 0) || e->type == SDL_CONTROLLERBUTTONDOWN) {
        Uint8& controllerKeyPressed = e->cbutton.button;
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonMelee || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_B)) {
            mStockedState = 1;
        } else if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRanged || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_X)) {
            mStockedState = 2;
        }
    }
    return nullptr;
}

CharacterState* MeleeAttackingState::handleLogic(Character& character, std::vector<SDL_Rect>*, double) {
    int spriteSize = character.mCharacterSprites["melee"].size();
    if(static_cast<int>(mCharStateTimer.getTicks())>= mActionDuration) {
        switch (mStockedState) {
            case 0:
            return new DoNothingState();
            break;
            case 1:
            return new MeleeAttackingState(character);
            break;
            case 2:
            return new RangedAttackingState(character);
        }
    }
    if(spriteSize) {
        int tickPerSprite = mActionDuration/spriteSize;
        character.mCurrentSprite = &character.mCharacterSprites["melee"][mCharStateTimer.getTicks() / tickPerSprite % spriteSize];
    }
    return nullptr;
}

void MeleeAttackingState::handleGraphics(Character&) {

}