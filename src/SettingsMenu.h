#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Locator.h"
#include "SoundEffect.h"
#include <vector>

class SettingsMenu : public GameState {
   public:
    SettingsMenu(Game* gameInstance);
    ~SettingsMenu();
    void handleEvents(SDL_Event* event);
    void handleLogic(double timeStep);
    void handleGraphics();
   private:
    IRenderer* gRenderer = Locator::getRenderer();
    Texture* mSpriteSheet1;
    int mChoosingOption;
    Texture* mStartButton;
    Texture* mSettingsButton;
    Texture* mCreditsButton;
    Texture* mExitButton;
    Texture* mBackgroundTexture;
    SoundEffect* mChooseSound;
    SoundEffect* mConfirmSound;
    std::vector<Sprite *> mBackground;
    Game* gCurrentGame;
    int accumulator;
};

#endif