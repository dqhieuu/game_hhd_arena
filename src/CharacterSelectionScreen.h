#ifndef CHARACTER_SELECTION_SCREEN_H
#define CHARACTER_SELECTION_SCREEN_H

#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Locator.h"
#include "SoundEffect.h"
#include <vector>

class CharacterSelectionScreen : public GameState {
   public:
    CharacterSelectionScreen(Game* gameInstance);
    ~CharacterSelectionScreen();
    void handleEvents(SDL_Event* event);
    void handleLogic(double timeStep);
    void handleGraphics();
   private:
    const int NUM_OF_OPTIONS = 3;
    IRenderer* gRenderer = Locator::getRenderer();
    int mChoosingOption;
    Texture mObjectSheet;
    Texture mCharHieu;
    Texture mCharHa;
    Texture mCharDuong;
    Texture mBackgroundTexture;
    Sprite mCharFrame;
    Sprite mCharFrameSelected;
    std::vector<Sprite> mBackground;
    Game* gCurrentGame;
};

#endif