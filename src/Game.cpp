#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Game.h"
#include "Stage1.h"

#include "Locator.h"


Game::Game() {
    mGameWindow = nullptr;
    mGameRenderer = nullptr;
    mCurrentState = nullptr;
    mCurrentStateId = NULL_STATE;
    mNextStateId = NULL_STATE;
}

Game::~Game() {
    delete mGameEvents;
    delete mCurrentState;
    SDL_DestroyRenderer(mGameRenderer);
    SDL_DestroyWindow(mGameWindow);
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool Game::initialize(std::string gameTitle, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error: SDL_Init: " << SDL_GetError() << "\n";
        return false;
    }

    // Initialize main window
    mGameWindow = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (mGameWindow == nullptr) {
        std::cout << "Error: SDL_CreateWindow: " << SDL_GetError() << "\n";
        return false;
    }

    // Inialize renderer attached to the main game window w/ vsync
    mGameRenderer = SDL_CreateRenderer(mGameWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mGameRenderer == nullptr) {
        std::cout << "Error: SDL_CreateRenderer: " << SDL_GetError() << "\n";
        return false;
    }

    // Set renderer
    Locator::getRenderer()->setRenderer(mGameRenderer, width, height);

    // Create event listener;
    mGameEvents = new SDL_Event();

    // Enable antialiasing
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "BEST");

    // Initialize image loader
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        std::cout << "Error: IMG_Init: " << IMG_GetError() << "\n";
        return false;
    }

    // Initialize audio loader
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cout << "Error: Mix_OpenAudio: " << Mix_GetError() << "\n";
        return false;
    }

    // Initialize TTF font loader
    if (TTF_Init() == -1) {
        std::cout << "Error: TTF_Init: " << TTF_GetError() << "\n";
        return false;
    }

    // Set first game state
    setState(STAGE_1);
    return true;
}


void Game::update(double timeStep) {
    checkState();
    Locator::getRenderer()->clearScreen();
    mCurrentState->handleEvents(mGameEvents);
    mCurrentState->handleLogic(timeStep);
    mCurrentState->render();
    SDL_RenderPresent(mGameRenderer);
}

void Game::setState(StateType state) {
    mNextStateId = state;
}

void Game::checkState() {
    if (mNextStateId != NULL_STATE) {
        if(mNextStateId != GAME_EXIT)
            delete mCurrentState;
        mCurrentStateId = mNextStateId;
        switch (mCurrentStateId) {
            case MAIN_MENU:
                //mCurrentState = new MainMenu();
                break;
            case STAGE_1:
                mCurrentState = new Stage1(this);
                break;
            default:
                break;
        }
         mNextStateId = NULL_STATE;
    }
}