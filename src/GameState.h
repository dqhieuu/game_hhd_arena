#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL.h>

enum StateType {
    NULL_STATE,
    MAIN_MENU,
    STAGE_1,
    SETTINGS,
    GAME_EXIT
};

class GameState {
   public:
    virtual void handleEvents(SDL_Event* event) = 0;
    virtual void handleLogic(double timeStep) = 0;
    virtual void render() = 0;
    virtual ~GameState(){};
};

#endif