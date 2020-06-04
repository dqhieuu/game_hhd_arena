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
    void setState(StateType state, std::string flags = "");
    SDL_GameController* getController() {return mController;}
    Settings mGameSettings;
    StateType mCurrentStateId;

    SDL_Haptic* mControllerHaptic;
   private:
    void checkState();
    StateType mNextStateId;
    std::string mNextStateFlags = "";
    SDL_Window* mGameWindow;
    SDL_Renderer* mGameRenderer;
    SDL_GameController* mController;
    SDL_Event* mGameEvents;
    GameState* mCurrentState;
    int mWidth;
    int mHeight;
};

#endif