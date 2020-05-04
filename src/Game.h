#ifndef GAME_H
#define GAME_H

#include <string>
#include "GameState.h"
#include "Settings.h"

class Game {
   public:
    Game();
    ~Game();
    bool initialize(std::string gameTitle, int width, int height);
    void update(double timeStep);
    void setState(StateType state);
    Settings mGameSettings;
    StateType mCurrentStateId;


   private:
    void checkState();
    StateType mNextStateId;
    SDL_Window* mGameWindow;
    SDL_Renderer* mGameRenderer;
    SDL_Event* mGameEvents;
    GameState* mCurrentState;
};

#endif