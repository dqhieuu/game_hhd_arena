#ifndef DO_NOTHING_STATE_H
#define DO_NOTHING_STATE_H

#include "Character.h"
#include "CharacterState.h"

class DoNothingState : public CharacterState {
    public:
    virtual CharacterState* handleInput(Character& character, SDL_Event* e);
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t);
    virtual void handleGraphics(Character& character);
};

#endif