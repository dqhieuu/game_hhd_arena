#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Locator.h"
#include "SoundEffect.h"
#include <vector>

class MainMenu : public GameState {
   public:
    MainMenu(Game* gameInstance);
    ~MainMenu();
    void handleEvents(SDL_Event* event);
    void handleLogic(double timeStep);
    void handleGraphics();
   private:
    const int NUM_OF_OPTIONS = 4;
    IRenderer* gRenderer = Locator::getRenderer();
    int mChoosingOption;
    Texture* mStartButton;
    Texture* mSettingsButton;
    Texture* mCreditsButton;
    Texture* mExitButton;
    Texture* mBackgroundTexture;
    std::vector<Sprite> mBackground;
    Game* gCurrentGame;
};

#endif