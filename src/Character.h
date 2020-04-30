#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>

#include "Sprite.h"
#include "SoundEffect.h"

enum Direction {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Character {
   public:
    Character(int x, int y);
    void handleEvent(SDL_Event* e);
    void handleGraphics();
    void move(double timeStep);
    int getPosX();
    int getPosY();
    void update(double timeStep);
    Sprite* getSprite();

   private:
    SoundEffect* mStep;
    Sprite* mCurrentSprite;
    Sprite* mMoveSprite[3];
    Texture* mSpriteTexture;
    double MAX_VEL_X = 800;
    double ACCELERATION = 2000;
    double GRAVITY = 1;
    int mAccumulator;
    Direction mMoveDirectionX, mMoveDirectionY;
    Direction mFacingDirection;
    double mX, mY;
    double mVelX, mVelY;
};

#endif