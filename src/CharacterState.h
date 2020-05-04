#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H
#include <vector>


#include "Locator.h"

class Character;

class CharacterState {
   public:
    virtual ~CharacterState() {}
    virtual CharacterState* handleInput(Character& character, SDL_Event* e) = 0;
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t) = 0;
    virtual void handleGraphics(Character& character) = 0;
};

#endif