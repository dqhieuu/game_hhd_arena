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

#include "Character.h"
#include "Game.h"
#include "GameState.h"
#include "Locator.h"
#include "MusicPlayer.h"
#include "Renderer.h"
#include "SoundEffect.h"
#include "SoundEffectPlayer.h"
#include "Sprite.h"
#include "Texture.h"
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

    // Main game loop

    while (myGame.mCurrentStateId != GAME_EXIT) {
        // Get fps every 500ms
        if (fpsCounter.getTicks() > 500) {
            double avgFPS = (double)countedFrames / fpsCounter.getTicks() * 1000;
            fpsCounter.start();  // Reset fps counter
            countedFrames = 0;
        } else
            ++countedFrames;

        //Get timestep and reset
        int frameTicks = stepTimer.getTicks();
        double timeStep = stepTimer.getTicks() / 1000.0;
        stepTimer.start();
        // Update the main game
        myGame.update(timeStep);

        // Delay if game run too fast
        if (frameTicks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - frameTicks);
        }

    }
    return 0;
}
