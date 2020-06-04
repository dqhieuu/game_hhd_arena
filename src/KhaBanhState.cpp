#include "KhaBanhState.h"

#include <chrono>
#include <random>
#include <vector>

#include "Character.h"
#include "CharacterState.h"
#include "JumpingState.h"
#include "Locator.h"
#include "Vector2D.h"
#include "utils.h"

CharacterState* KhaBanhState::handleInput(Character&, SDL_Event*) {
    return nullptr;
}

CharacterState* KhaBanhState::handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t) {
    int charWidth = character.mWidth;
    int charHeight = character.mHeight;
    character.mCurrentSprite = &character.mCharacterSprites["stand"][mCharStateTimer.getTicks() / 200 % character.mCharacterSprites["stand"].size()];

    SDL_Rect solidBoxChar = Locator::getRenderer()->getAbsolutePosition(character.getCurrentSprite()->getTexture(), character.getPosX(), character.getPosY(), charWidth, charHeight);
    std::mt19937 rng(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 1);
    std::uniform_int_distribution<int> dist2(0, 1);
    std::uniform_int_distribution<int> dist3(0, 10);
    std::uniform_int_distribution<int> dist4(0, 100);
    std::vector<Vector2D> airbornePos = {{100, 100}, {400, 100}, {700, 100}, {1100, 100}};
    std::uniform_int_distribution<int> distPos(0, airbornePos.size()-1);

    if (!mIsDoingAction) {
        if (character.mHitPoints <= 500) {
        } else {
            mActionTimer.start();
            mIsDoingAction = true;
            int choice = dist(rng);
            mActionState = choice;
            switch (mActionState) {
                case 1:
                    if(!mHasSaidPill) {
                        Locator::getSoundEffectPlayer()->play("choido");
                    }
                    mStatePhase = 0;
                    if (character.mPos.x < 600) {
                        mMoveDest = *airbornePos.begin();
                    } else {
                        mMoveDest = airbornePos.back();
                    }
                    mMoveDeg = (mMoveDest - character.mPos).getRotateDeg();
                    mMoveVect = Vector2D(600, 0).rotate(mMoveDeg);
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
            }
        }
    } else {
        switch (mActionState) {
            case 1:
                if (mStatePhase == 0) {
                    if ((character.mPos - mMoveDest).length() <= 20) {
                        character.mPos = mMoveDest;
                        mStatePhase = 1;
                        mStateShootFired = 0;
                        mActionTimer.start();
                    } else {
                        if(!mHasSaidPill) {
                            if(mActionTimer.getTicks()>=4500) mHasSaidPill=true;
                        } else {
                            character.mPos += mMoveVect * t;
                        }
                    }
                } else if (mStatePhase == 1) {
                    std::uniform_int_distribution<int> distPill(0, character.mCharacterSprites["pill"].size() - 1);
                    if (mActionTimer.getTicks() >= 1500) {
                        if(mStateShootFired<5) {
                        int pillType = distPill(rng);
                        switch (pillType) {
                            case 0:
                            case 3:
                                Locator::getSoundEffectPlayer()->play("vienthuockeo");
                                break;
                            case 1:
                                Locator::getSoundEffectPlayer()->play("vienthuockimcuong");
                                break;
                            case 2:
                                Locator::getSoundEffectPlayer()->play("vienthuocvuongliem");
                                break;
                            case 4:
                                Locator::getSoundEffectPlayer()->play("vienthuocaxitb1");
                                break;
                        }
                        character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new LinearBullet(*character.gGameStateInstance, &character.mCharacterSprites["pill"][pillType], character.mPos.x, character.mPos.y, 50, 40, 800, 30, (character.mEnemyPos - character.mPos).getRotateDeg())));
                        character.mCharacterBullets.back()->start();
                        for (int i = 0; i < 5; ++i) {
                            double deg;
                            if(dist2(rng)) {
                                deg = 5+dist3(rng)/2;
                            } else {
                                deg = -5-dist3(rng)/2;
                            }
                            character.mCharacterBullets.push_back(std::unique_ptr<Bullet>(new LinearBullet(*character.gGameStateInstance, &character.mCharacterSprites["pill"][pillType], character.mPos.x, character.mPos.y, 50, 40, 800, 30, (character.mEnemyPos - character.mPos).getRotateDeg()+deg)));
                            character.mCharacterBullets.back()->start();
                        }
                        ++mStateShootFired;
                        mActionTimer.start();
                        } else if(mActionTimer.getTicks() >= 2000) {
                            mStatePhase = 2;
                        }
                    }
                } else if (mStatePhase == 2) {
                    mMoveDest = airbornePos[distPos(rng)];
                    mMoveDeg = (mMoveDest - character.mPos).getRotateDeg();
                    mMoveVect = Vector2D(200, 0).rotate(mMoveDeg);
                    mStatePhase = 0;
                }
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    }

    return nullptr;
}

void KhaBanhState::handleGraphics(Character& character) {
}