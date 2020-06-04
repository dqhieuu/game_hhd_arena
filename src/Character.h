#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>

#include "Game.h"
#include "GameState.h"
#include "SoundEffect.h"
#include "Sprite.h"
#include <vector>
#include <unordered_map>
#include "Vector2D.h"
#include <utility>
#include "Bullet.h"
#include <string>

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
    Character(Game* gameInstance, GameState* gameStateInstance, int x, int y, std::string character);
    ~Character();
    void handleEvent(SDL_Event* e);
    void handleLogic(std::vector<SDL_Rect>* solidObjects, double timeStep);
    void handleGraphics();
    void move(double timeStep, bool isFalling);
    void jump();
    void directionalJump(Direction direction);
    void fire();
    int getPosX();
    int getPosY();
    Sprite* getCurrentSprite();
    void addSpriteSheet(std::string name, std::string path);
    void addSprite(std::string type, std::string sheetName, int x, int y, int w, int h, bool defaultHitBox=false);
    void decreaseHP(int HP=0);
    void transferBullet(std::vector<std::unique_ptr<Bullet>>& bullets);
    void overrideBossState();
    void setEnemyPos(Vector2D pos);

  // private:
    friend class StandingState;
    friend class JumpingState;
    friend class WallSlidingState;
    friend class DoNothingState;
    friend class MeleeAttackingState;
    friend class RangedAttackingState;
    CharacterState* mCurrentState;
    CharacterState* mCurrentActionState;

    std::vector<std::unique_ptr<Bullet>> mCharacterBullets;
    std::unordered_map<std::string, Texture> mSpriteSheets;
    SpriteDictionary mCharacterSprites;

    Sprite* mCurrentSprite;

    Texture* mSpriteTexture;
    int MAX_HP = 200;
    int MAX_MP = 100;
    double MAX_VEL_X = 650;
    double ACCELERATION = 2500;
    double GRAVITY = 2500;
    double JUMP_VELOCITY = 900;
    int MAX_JUMP_COUNT = 2;
    int mJumpLeft;
    int mHitPoints;
    int mManaPoints;
    int mInvincibleTick = 1500;
    Direction mMoveDirectionX, mMoveDirectionY;
    Direction mFacingDirection;
    int mWidth;
    int mHeight;
    
    Vector2D mPos;
    Vector2D mVel;
    Vector2D mEnemyPos;
    Game* gGameInstance;
    GameState* gGameStateInstance;
    TTF_Font *mCharFont;
    Timer mCharTimer;
    Timer mCharInvincibleTimer;
    std::string mCharName;
};

#endif