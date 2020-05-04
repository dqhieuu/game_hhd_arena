#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>

#include "Game.h"
#include "SoundEffect.h"
#include "Sprite.h"
#include <vector>

enum Direction {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class CharacterState;

class Character {
   public:
    Character(Game* gGameInstance, int x, int y);
    void handleEvent(SDL_Event* e);
    void handleLogic(std::vector<SDL_Rect>* solidObjects, double timeStep);
    void handleGraphics();
    void move(double timeStep);
    void jump(double timeStep);
    int getPosX();
    int getPosY();
    Sprite* getSprite();

   private:
    friend class StandingState;
    friend class JumpingState;
    CharacterState* mCurrentState;
    SoundEffect* mStep;
    Sprite* mCurrentSprite;
    Sprite* mStandingSprite[2];
    Sprite* mMoveSprite[3];
    Sprite* mJumpingSprite[2];
    Texture* mSpriteTexture;
    double MAX_VEL_X = 650;
    double ACCELERATION = 2000;
    double GRAVITY = 2200;
    double JUMP_VELOCITY = 1000;
    int MAX_JUMP_COUNT = 2;
    int mJumpLeft;
    int mAccumulator;
    Direction mMoveDirectionX, mMoveDirectionY;
    Direction mFacingDirection;
    double mX, mY;
    double mVelX, mVelY;
    Game* gGameInstance;
    int mHitPoints;
};

#endif