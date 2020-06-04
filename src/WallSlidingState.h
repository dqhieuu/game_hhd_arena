#ifndef WALL_SLIDING_STATE_H
#define WALL_SLIDING_STATE_H

#include "Character.h"
#include "CharacterState.h"

class WallSlidingState : public CharacterState {
    public:
    WallSlidingState(Character* character) {
        gCharacter = character;
        Locator::getSoundEffectPlayer()->play("slide", -1);
        mCharStateTimer.start();
    }
    virtual ~WallSlidingState() {
        Locator::getSoundEffectPlayer()->stop("slide");
    }
    virtual CharacterState* handleInput(Character& character, SDL_Event* e);
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t);
    virtual void handleGraphics(Character& character);
    private:
    Character* gCharacter;
};

#endif