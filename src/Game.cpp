#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cereal/archives/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "CharacterSelectionScreen.h"
#include "Intro.h"
#include "Locator.h"
#include "MainMenu.h"
#include "Settings.h"
#include "Stage1.h"
#include "StageResult.h"

Game::Game() {
    mWidth = 0;
    mHeight = 0;
    mGameWindow = nullptr;
    mGameRenderer = nullptr;
    mController = nullptr;
    mCurrentState = nullptr;
    mCurrentStateId = NULL_STATE;
    mNextStateId = NULL_STATE;
}

Game::~Game() {
    delete mGameEvents;
    delete mCurrentState;
    SDL_GameControllerClose(mController);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(mGameRenderer);
    SDL_DestroyWindow(mGameWindow);
    SDL_Quit();
}

bool Game::initialize(std::string gameTitle, int width, int height) {
    {  // Read game settings by deserialization (encapsulation to ensure cereal's RAII)
        std::ifstream readSettingsFile("settings.dat");
        if (!readSettingsFile) {
            std::ofstream writeSettingsFile("settings.dat");
            cereal::JSONOutputArchive writeArchive(writeSettingsFile);
            writeArchive(CEREAL_NVP(mGameSettings));
            std::cout << "Created new settings file.\n";
        } else {
            cereal::JSONInputArchive readArchive(readSettingsFile);
            readArchive(mGameSettings);
        }
    }

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

    // Set width, height
    mWidth = width;
    mHeight = height;

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

    // Set antialiasing based on the attribute setting
    if (mGameSettings.gameQuality == HIGH || mGameSettings.gameQuality == MEDIUM) {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    } else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    }

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
    Mix_AllocateChannels(200);

    // Set music player volume based on the attribute setting
    Locator::getMusicPlayer()->setVolume(mGameSettings.musicVolume);

    // Set sound effect volumes based on the attribute setting
    Locator::getSoundEffectPlayer()->setVolume(mGameSettings.effectsVolume);

    // Initialize TTF font loader
    if (TTF_Init() == -1) {
        std::cout << "Error: TTF_Init: " << TTF_GetError() << "\n";
        return false;
    }

    // Disable cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Set fullscreen based on the attribute setting
    if (mGameSettings.isFullScreen == true) {
        SDL_SetWindowFullscreen(mGameWindow, SDL_WINDOW_FULLSCREEN);
    }

    // Initialize controller
    if (SDL_NumJoysticks() < 1) {
        std::cout << "Warning: No controller connected!\n";
    } else {
        mController = SDL_GameControllerOpen(0);
        if (mController == nullptr) {
            std::cout << "Warning: Unable to open game controller! SDL Error: "<< SDL_GetError() << "\n";
        } else {
            mControllerHaptic = SDL_HapticOpen(0);
            if(mControllerHaptic != nullptr) {
                SDL_HapticRumbleInit(mControllerHaptic);
            }
        }
    }

    // Set first game state
    setState(INTRO);

    return true;
}

void Game::update(double timeStep) {
    checkState();
    Locator::getRenderer()->clearScreen();
    mCurrentState->handleEvents(mGameEvents);
    mCurrentState->handleLogic(timeStep);
    mCurrentState->handleGraphics();
    SDL_RenderPresent(mGameRenderer);
}

void Game::setState(StateType state, std::string flags) {
    mNextStateId = state;
    mNextStateFlags = flags;
}

void Game::checkState() {
    if (mNextStateId != NULL_STATE) {
        if (mNextStateId != GAME_EXIT)
            delete mCurrentState;
        mCurrentStateId = mNextStateId;
        switch (mCurrentStateId) {
            case INTRO:
                mCurrentState = new Intro(this);
                break;
            case MAIN_MENU:
                mCurrentState = new MainMenu(this);
                break;
            case CHARACTER_SELECTION:
                mCurrentState = new CharacterSelectionScreen(this);
                break;
            case STAGE_1:
                mCurrentState = new Stage1(this, mWidth, mHeight, mNextStateFlags);
                break;
            case STAGE_RESULT:
                mCurrentState = new StageResult(this, mNextStateFlags);
            default:
                break;
        }
        mNextStateId = NULL_STATE;
        mNextStateFlags = "";
    }
}