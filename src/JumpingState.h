#ifndef JUMPING_STATE_H
#define JUMPING_STATE_H
#include "CharacterState.h"
#include "Character.h"

class JumpingState : public CharacterState {
   public:
    JumpingState() {mCharStateTimer.start();}
    virtual CharacterState* handleInput(Character& character, SDL_Event* e);
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t);
    virtual void handleGraphics(Character& character);
};

#endif