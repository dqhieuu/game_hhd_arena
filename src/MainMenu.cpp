#include "MainMenu.h"

#include <SDL_ttf.h>

#include "Locator.h"
#include "Renderer.h"

MainMenu::MainMenu(Game* gameInstance) {
    gCurrentGame = gameInstance;
    mChoosingOption = 0;
    mGameStateTimer.start();
    TTF_Font* font1 = TTF_OpenFont("assets/fonts/FVF Fernando 08.ttf", 24);
    SDL_Color white = {255, 255, 255, 255};
    mStartButton = new Texture(font1, "Bắt đầu", white);
    mSettingsButton = new Texture(font1, "Cài đặt", white);
    mCreditsButton = new Texture(font1, "Credits", white);
    mExitButton = new Texture(font1, "Thoát game", white);
    TTF_CloseFont(font1);
    mBackgroundTexture = new Texture("assets/img/main-menu-bg.png");
    for (int i = 0; i < 10; ++i) {

        mBackground.push_back(Sprite(mBackgroundTexture, 0, 535 * i, 1024, 535));
    }
    Locator::getMusicPlayer()->load("assets/bgm/calm_main_menu_theme.mp3");
    Locator::getMusicPlayer()->play();
    Locator::getMusicPlayer()->setInternalVolume(100);
    Locator::getSoundEffectPlayer()->loadSoundEffect("choose","assets/se/choose.wav");
    Locator::getSoundEffectPlayer()->loadSoundEffect("confirm","assets/se/confirm.wav");
}
MainMenu::~MainMenu() {
    delete mBackgroundTexture;
    delete mStartButton;
    delete mSettingsButton;
    delete mCreditsButton;
    delete mExitButton;
}

void MainMenu::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if ((event->type == SDL_KEYDOWN && event->key.repeat == 0) || event->type == SDL_CONTROLLERBUTTONDOWN) {
            SDL_Scancode& keyPressed = event->key.keysym.scancode;
            Uint8& controllerKeyPressed = event->cbutton.button;
            if (keyPressed == SDL_SCANCODE_DOWN || keyPressed == gCurrentGame->mGameSettings.buttonDown || (event->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
                Locator::getSoundEffectPlayer()->play("choose");
                mChoosingOption = (mChoosingOption + 1) % NUM_OF_OPTIONS;
            } else if (keyPressed == SDL_SCANCODE_UP || keyPressed == gCurrentGame->mGameSettings.buttonUp ||  (event->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_UP)) {
                Locator::getSoundEffectPlayer()->play("choose");
                if (mChoosingOption == 0)
                    mChoosingOption = NUM_OF_OPTIONS-1;
                else
                    --mChoosingOption;
            } else if (keyPressed == SDL_SCANCODE_RETURN || keyPressed == SDL_SCANCODE_SPACE || keyPressed == gCurrentGame->mGameSettings.buttonJump || (event->type == SDL_CONTROLLERBUTTONDOWN && (controllerKeyPressed == SDL_CONTROLLER_BUTTON_A || controllerKeyPressed == SDL_CONTROLLER_BUTTON_START))) {
                Locator::getSoundEffectPlayer()->play("confirm");
                switch(mChoosingOption) {
                    case 0:
                    gCurrentGame->setState(CHARACTER_SELECTION);
                    break;
                    case 1:

                    break;
                    case 2:

                    break;
                    case 3:
                    gCurrentGame->setState(GAME_EXIT);
                    break;
                }
            }
        }
    }
}

void MainMenu::handleLogic(double) {

}

void MainMenu::handleGraphics() {
    Sprite* currentBG = &mBackground[mGameStateTimer.getTicks() / 100 % 10];

    // Reset transparency
    gRenderer->setTextureTransparency(mStartButton, 255);
    gRenderer->setTextureTransparency(mSettingsButton, 255);
    gRenderer->setTextureTransparency(mCreditsButton, 255);
    gRenderer->setTextureTransparency(mExitButton, 255);

    switch(mChoosingOption) {
        case 0:
        gRenderer->setTextureTransparency(mStartButton, 100);
        break;
        case 1:
        gRenderer->setTextureTransparency(mSettingsButton, 100);
        break;
        case 2:
        gRenderer->setTextureTransparency(mCreditsButton, 100);
        break;
        case 3:
        gRenderer->setTextureTransparency(mExitButton, 100);
        break;
    }
    gRenderer->renderTexture(currentBG->getTexture(), currentBG->getClip());
    SDL_Rect pos1 = gRenderer->getAbsolutePosition(mStartButton, 20, 165, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mStartButton, nullptr, &pos1);
    SDL_Rect pos2 = gRenderer->getAbsolutePosition(mSettingsButton, 20, 245, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mSettingsButton, nullptr, &pos2);
    SDL_Rect pos3 = gRenderer->getAbsolutePosition(mCreditsButton, 20, 325, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mCreditsButton, nullptr, &pos3);
    SDL_Rect pos4 = gRenderer->getAbsolutePosition(mExitButton, 20, 400, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mExitButton, nullptr, &pos4);
}
