#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL.h>
#include "Timer.h"

enum StateType {
    NULL_STATE,
    INTRO,
    MAIN_MENU,
    SETTINGS,
    CHARACTER_SELECTION,
    STAGE_1,
    STAGE_RESULT,
    CREDITS,
    GAME_EXIT
};

class GameState {
   public:
    virtual void handleEvents(SDL_Event* event) = 0;
    virtual void handleLogic(double timeStep) = 0;
    virtual void handleGraphics() = 0;
    int getWidth() {return mWidth;}
    int getHeight() {return mHeight;}
    virtual ~GameState(){};
   protected:
    int mWidth = 0;
    int mHeight = 0;
    Timer mGameStateTimer;
};

#endif