#ifndef RANGED_ATTACKING_STATE_H
#define RANGED_ATTACKING_STATE_H

#include "Character.h"
#include "CharacterState.h"

class RangedAttackingState : public CharacterState {
    public:
    RangedAttackingState(Character& character);
    virtual CharacterState* handleInput(Character& character, SDL_Event* e);
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t);
    virtual void handleGraphics(Character& character);
    int mActionDuration;
    int mStockedState;
};

#endif