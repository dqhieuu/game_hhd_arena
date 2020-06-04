#include "CharacterSelectionScreen.h"

#include <SDL_ttf.h>

#include "Renderer.h"

CharacterSelectionScreen::CharacterSelectionScreen(Game* gameInstance) {
    gCurrentGame = gameInstance;
    mGameStateTimer.start();
    mChoosingOption = 0;
    TTF_Font* font1 = TTF_OpenFont("assets/fonts/FVF Fernando 08.ttf", 24);
    SDL_Color white = {255, 255, 255, 255};
    mCharHieu.loadFromRenderedText(font1, "NV Hiếu", white);
    mCharHa.loadFromRenderedText(font1, "NV Hà", white);
    mCharDuong.loadFromRenderedText(font1, "NV Dương", white);
    TTF_CloseFont(font1);
    mBackgroundTexture.loadFromFile("assets/img/not-main-menu-bg.png");
    mObjectSheet.loadFromFile("assets/img/objectsheet.png");
    mCharFrame.setSprite(&mObjectSheet, 403, 313, 103, 130);
    mCharFrameSelected.setSprite(&mObjectSheet, 535, 313, 103, 130);
    for (int i = 0; i < 8; ++i)
        mBackground.push_back(Sprite(&mBackgroundTexture, 0, 282 * i, 500, 282));
}
CharacterSelectionScreen::~CharacterSelectionScreen() {

}

void CharacterSelectionScreen::handleEvents(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            gCurrentGame->setState(GAME_EXIT);
        else if ((event->type == SDL_KEYDOWN && event->key.repeat == 0) || ( event->type == SDL_CONTROLLERBUTTONDOWN)) {
            SDL_Scancode& keyPressed = event->key.keysym.scancode;
            Uint8& controllerKeyPressed = event->cbutton.button;
            if (keyPressed == SDL_SCANCODE_RIGHT || keyPressed == gCurrentGame->mGameSettings.buttonRight || (event->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
                Locator::getSoundEffectPlayer()->play("choose");
                mChoosingOption = (mChoosingOption + 1) % NUM_OF_OPTIONS;
            } else if (keyPressed == SDL_SCANCODE_LEFT || keyPressed == gCurrentGame->mGameSettings.buttonLeft || (event->type == SDL_CONTROLLERBUTTONDOWN && controllerKeyPressed == SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
                Locator::getSoundEffectPlayer()->play("choose");
                if (mChoosingOption == 0)
                    mChoosingOption = NUM_OF_OPTIONS-1;
                else
                    --mChoosingOption;
            } else if (keyPressed == SDL_SCANCODE_RETURN || keyPressed == SDL_SCANCODE_SPACE || keyPressed == gCurrentGame->mGameSettings.buttonJump || (event->type == SDL_CONTROLLERBUTTONDOWN && (controllerKeyPressed == SDL_CONTROLLER_BUTTON_A || controllerKeyPressed == SDL_CONTROLLER_BUTTON_START))) {
                Locator::getSoundEffectPlayer()->play("confirm");
                switch(mChoosingOption) {
                    case 0:
                    gCurrentGame->setState(STAGE_1, "Hieu");
                    break;
                    case 1:
            //        gCurrentGame->setState(STAGE_1, "Ha");
                    break;
                    case 2:
                    gCurrentGame->setState(STAGE_1, "Duong");
                    break;
                }
            } else if (keyPressed == SDL_SCANCODE_BACKSPACE || keyPressed == SDL_SCANCODE_ESCAPE || keyPressed == gCurrentGame->mGameSettings.buttonMelee || (event->type == SDL_CONTROLLERBUTTONDOWN && (controllerKeyPressed == SDL_CONTROLLER_BUTTON_B || controllerKeyPressed == SDL_CONTROLLER_BUTTON_BACK))) {
                Locator::getSoundEffectPlayer()->play("confirm");
                gCurrentGame->setState(MAIN_MENU);
            }
        }
    }
}

void CharacterSelectionScreen::handleLogic(double) {

}

void CharacterSelectionScreen::handleGraphics() {
    Sprite* currentBG = &mBackground[mGameStateTimer.getTicks() / 100 % 8];
    gRenderer->renderTexture(currentBG->getTexture(), currentBG->getClip());
    SDL_Rect pos1 = gRenderer->getAbsolutePosition(mCharFrame.getTexture(), -300, 0, 200, 270, PIN_CENTER, PIN_CENTER);
    gRenderer->renderTexture(mCharFrame.getTexture(), mCharFrame.getClip(), &pos1);

    SDL_Rect pos2 = gRenderer->getAbsolutePosition(mCharFrame.getTexture(), 0, 0, 200, 270, PIN_CENTER, PIN_CENTER);
    gRenderer->renderTexture(mCharFrame.getTexture(), mCharFrame.getClip(), &pos2);

    SDL_Rect pos3 = gRenderer->getAbsolutePosition(mCharFrame.getTexture(), 300, 0, 200, 270, PIN_CENTER, PIN_CENTER);
    gRenderer->renderTexture(mCharFrame.getTexture(), mCharFrame.getClip(), &pos3);

    switch(mChoosingOption) {
        case 0:
        gRenderer->renderTexture(mCharFrameSelected.getTexture(), mCharFrameSelected.getClip(), &pos1);
        break;
        case 1:
        gRenderer->renderTexture(mCharFrameSelected.getTexture(), mCharFrameSelected.getClip(), &pos2);
        break;
        case 2:
       gRenderer->renderTexture(mCharFrameSelected.getTexture(), mCharFrameSelected.getClip(), &pos3);
        break;
    }
        SDL_Rect pos4 = gRenderer->getAbsolutePosition(&mCharHieu, -300, 0, -1, 50, PIN_CENTER, PIN_CENTER);
    gRenderer->renderTexture(&mCharHieu, nullptr, &pos4);
        SDL_Rect pos5 = gRenderer->getAbsolutePosition(&mCharHa, 0, 0, -1, 50, PIN_CENTER, PIN_CENTER);
    gRenderer->renderTexture(&mCharHa, nullptr, &pos5);
        SDL_Rect pos6 = gRenderer->getAbsolutePosition(&mCharDuong, 300, 0, -1, 50, PIN_CENTER, PIN_CENTER);
    gRenderer->renderTexture(&mCharDuong, nullptr, &pos6);
}
