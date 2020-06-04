#include "DoNothingState.h"

#include "Locator.h"
#include "MeleeAttackingState.h"
#include "RangedAttackingState.h"

CharacterState* DoNothingState::handleInput(Character& character, SDL_Event* e) {
    if ((e->type == SDL_KEYDOWN && e->key.repeat == 0) || e->type == SDL_CONTROLLERBUTTONDOWN) {
        Uint8& controllerKeyPressed = e->cbutton.button;
        if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonMelee || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_B)) {
            return new MeleeAttackingState(character);
        } else if (e->key.keysym.scancode == character.gGameInstance->mGameSettings.buttonRanged || (e->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_X)) {
            return new RangedAttackingState(character);
        }
    }
    return nullptr;
}

CharacterState* DoNothingState::handleLogic(Character&, std::vector<SDL_Rect>*, double) {
    return nullptr;
}

void DoNothingState::handleGraphics(Character&) {
}