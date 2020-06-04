#ifndef STANDING_STATE_H
#define STANDING_STATE_H

#include "Character.h"
#include "CharacterState.h"

class StandingState : public CharacterState {
    public:
    StandingState() {mCharStateTimer.start();}
    virtual CharacterState* handleInput(Character& character, SDL_Event* e);
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t);
    virtual void handleGraphics(Character& character);
    bool mRunSoundOn = true;
};

#endif