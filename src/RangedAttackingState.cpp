#include "DoNothingState.h"

#include "Locator.h"
#include "RangedAttackingState.h"
#include "MeleeAttackingState.h"
#include "Bullet.h"


RangedAttackingState::RangedAttackingState(Character& character) {
    Locator::getSoundEffectPlayer()->play("ranged");
    double degree = 0;
    if(character.mFacingDirection == LEFT) {
        degree=180;
    }
    if(character.mCharName == "Duong") {
    character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new LinearBullet(*character.gGameStateInstance, &character.mCharacterSprites["bullet"][0], character.mPos.x, character.mPos.y-35, 50, 35, 1000, 20, degree, 0, 700, true)));

    } else {
    character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new LinearBullet(*character.gGameStateInstance, &character.mCharacterSprites["bullet"][0], character.mPos.x, character.mPos.y-20, 50, 30, 2000, 30, degree)));
    }
    character.mCharacterBullets.back()->start();
    mCharStateTimer.start();
    mActionDuration = 300;
    mStockedState = 0;
}

CharacterState* RangedAttackingState::handleInput(Character& character, SDL_Event* e) {
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

CharacterState* RangedAttackingState::handleLogic(Character& character, std::vector<SDL_Rect>*, double) {
    int spriteSize = character.mCharacterSprites["ranged"].size();
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
        character.mCurrentSprite = &character.mCharacterSprites["ranged"][mCharStateTimer.getTicks() / tickPerSprite % spriteSize];
    }
    return nullptr;
}

void RangedAttackingState::handleGraphics(Character&) {

}