#include "MainMenu.h"

#include <SDL_ttf.h>

#include "Locator.h"
#include "Renderer.h"

MainMenu::MainMenu(Game* gameInstance) {
    mChoosingOption = 0;
    gCurrentGame = gameInstance;
    TTF_Font* font1 = TTF_OpenFont("assets/fonts/FVF Fernando 08.ttf", 24);
    SDL_Color white = {255, 255, 255, 255};
    mStartButton = new Texture(font1, "Bắt đầu", white);
    mSettingsButton = new Texture(font1, "Cài đặt", white);
    mCreditsButton = new Texture(font1, "Credits", white);
    mExitButton = new Texture(font1, "Thoát game", white);
    TTF_CloseFont(font1);
    mBackgroundTexture = new Texture("assets/img/settings-bg.png");
    for (int i = 0; i < 8; ++i) mBackground.push_back(new Sprite(mBackgroundTexture, 0, 282 * i, 500, 282));
    Locator::getMusicPlayer()->load("assets/bgm/calm_main_menu_theme.mp3");
    Locator::getMusicPlayer()->play();
    Locator::getMusicPlayer()->setInternalVolume(100);
    mChooseSound = new SoundEffect("assets/se/choose.wav");
    Locator::getSoundEffectPlayer()->loadSoundEffect(*mChooseSound);
    mConfirmSound = new SoundEffect("assets/se/confirm.wav");
    Locator::getSoundEffectPlayer()->loadSoundEffect(*mConfirmSound);
}
MainMenu::~MainMenu() {
    delete mBackgroundTexture;
    delete mStartButton;
    delete mSettingsButton;
    delete mCreditsButton;
    delete mExitButton;
    for (auto& elem : mBackground)
        delete elem;
}

void MainMenu::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
            SDL_Scancode& keyPressed = event->key.keysym.scancode;
            if (keyPressed == SDL_SCANCODE_DOWN || keyPressed == gCurrentGame->mGameSettings.buttonDown) {
                Locator::getSoundEffectPlayer()->play("choose");
                mChoosingOption = (mChoosingOption + 1) % 4;
            } else if (keyPressed == SDL_SCANCODE_UP || keyPressed == gCurrentGame->mGameSettings.buttonUp) {
                Locator::getSoundEffectPlayer()->play("choose");
                if (mChoosingOption == 0)
                    mChoosingOption = 3;
                else
                    --mChoosingOption;
            } else if (keyPressed == SDL_SCANCODE_RETURN || keyPressed == SDL_SCANCODE_SPACE || keyPressed == gCurrentGame->mGameSettings.buttonJump) {
                Locator::getSoundEffectPlayer()->play("choose");
                switch(mChoosingOption) {
                    case 0:
                    gCurrentGame->setState(STAGE_1);
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
    accumulator++;
}

void MainMenu::handleGraphics() {
    Sprite* currentBG = mBackground[accumulator / 5 % 8];

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
    SDL_Rect pos1 = Locator::getRenderer()->getAbsolutePosition(mStartButton, 20, 165, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mStartButton, nullptr, &pos1);
    SDL_Rect pos2 = Locator::getRenderer()->getAbsolutePosition(mSettingsButton, 20, 245, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mSettingsButton, nullptr, &pos2);
    SDL_Rect pos3 = Locator::getRenderer()->getAbsolutePosition(mCreditsButton, 20, 325, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mCreditsButton, nullptr, &pos3);
    SDL_Rect pos4 = Locator::getRenderer()->getAbsolutePosition(mExitButton, 20, 400, -1, 70, PIN_RIGHT, PIN_TOP);
    gRenderer->renderTexture(mExitButton, nullptr, &pos4);
}
