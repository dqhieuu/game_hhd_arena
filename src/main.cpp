#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Game.h"
#include "GameState.h"
#include "Locator.h"
#include "Timer.h"


int main(int /*argc*/, char** /*args*/) {
    // Game constants
    const static int SCREEN_WIDTH = 1280;
    const static int SCREEN_HEIGHT = 720;
    const static char GAME_TITLE[] = "HHD Arena";
    const static int SCREEN_FPS = 60;
    const static int TICKS_PER_FRAME = 1000 / SCREEN_FPS;  // must be an int

    // Instantiate a Game class and initialize libraries
    Game myGame;
    if (!myGame.initialize(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cout << "Initialization error.";
        return 1;
    }

    Timer stepTimer;
    Timer fpsCounter;
    int countedFrames = 0;
    fpsCounter.start();
    stepTimer.start();
    // Main game loop
    double timeStep;
    while (myGame.mCurrentStateId != GAME_EXIT) {
        // Get fps every 500ms
        if (fpsCounter.getTicks() >= 500) {
            double avgFPS = (double)countedFrames / fpsCounter.getTicks() * 1000;
            std:: cout << "FPS: " << avgFPS << "\n";
            fpsCounter.start();  // Reset fps counter
            countedFrames = 0;
        } else
            ++countedFrames;

        //Get previous time step and reset step timer
        timeStep = stepTimer.getTicks() / 1000.0;
        if(timeStep > 100) timeStep = 100;
        stepTimer.start();

        // Update the main game
        myGame.update(timeStep);

        // Get passed time step
        int tickPassed = stepTimer.getTicks();

        // Delay if game run too fast
        if (tickPassed < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - tickPassed);
        }
    }
    return 0;
}
