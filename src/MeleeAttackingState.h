#ifndef MELEE_ATTACKING_STATE_H
#define MELEE_ATTACKING_STATE_H

#include "Character.h"
#include "CharacterState.h"

class MeleeAttackingState : public CharacterState {
    public:
    MeleeAttackingState(Character& character);
    virtual CharacterState* handleInput(Character& character, SDL_Event* e);
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t);
    virtual void handleGraphics(Character& character);
    int mActionDuration;
    int mStockedState = 0;
};

#endif