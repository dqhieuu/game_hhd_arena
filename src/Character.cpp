#include "Character.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <cstdlib>
#include <string>
#include <vector>

#include "Locator.h"
#include "SoundEffect.h"
#include "Sprite.h"
#include "Texture.h"
#include "CharacterState.h"
#include "JumpingState.h"
#include "StandingState.h"
#include "DoNothingState.h"
#include "KhaBanhState.h"

Character::Character(Game* gameInstance, GameState* gameStateInstance, int x, int y, std::string character) {
    mCharName = character;
    mCharTimer.start();
    mMoveDirectionX = mMoveDirectionY = NONE;
    mFacingDirection = RIGHT;
    mPos.x=x;
    mPos.y=y;
    mWidth=80;
    mHeight=140;
    addSpriteSheet("objectsheet", "assets/img/objectsheet.png");
    Locator::getSoundEffectPlayer()->loadSoundEffect("charhurt","assets/se/female-hurt.wav");
    if(character == "Duong") {
        mHeight = 50;
        mWidth = 30;
        MAX_HP = 250;
        MAX_MP = 100;
        MAX_VEL_X = 650;
        ACCELERATION = 2500;
        GRAVITY = 2500;
        JUMP_VELOCITY = 900;
        MAX_JUMP_COUNT = 2;
        addSpriteSheet("charsheet", "assets/img/charduongfixed.png");
        addSprite("stand", "charsheet",  10, 28, 73, 133, true);
        addSprite("stand", "charsheet",  287, 28, 73, 133, true);
        addSprite("jump", "charsheet",  10, 28, 73, 133, true);
        addSprite("stand(option)", "charsheet",  119, 24, 73, 133, true);
        addSprite("stand(option)", "charsheet",  198, 26, 73, 133, true);
        addSprite("move", "charsheet",  2, 198, 88, 133, true);
        addSprite("move", "charsheet",  95, 198, 80, 133, true);
        addSprite("melee", "charsheet",  225, 191, 80, 133, true);
        addSprite("melee", "charsheet",  338, 191, 95, 133, true);
        addSprite("melee", "charsheet",  449, 191, 80, 133, true);
        addSprite("wallslide", "charsheet",  14, 343, 86, 141, true);
        addSprite("ranged", "charsheet",  225, 191, 80, 133, true);
        addSprite("ranged", "charsheet",  258, 351, 97, 133, true);
        addSprite("bullet","charsheet",  410,388,43,32, true);
        Locator::getSoundEffectPlayer()->loadSoundEffect("ranged","assets/se/projectileflying.wav");
        Locator::getSoundEffectPlayer()->loadSoundEffect("melee","assets/se/projectileflying.wav");

    } else if(character == "KhaBanh") {
        mWidth = 80;
        mHeight = 200;
        MAX_HP = 2500;
        MAX_MP = 100;
        MAX_VEL_X = 800;
        ACCELERATION = 3000;
        GRAVITY = 2500;
        JUMP_VELOCITY = 1200;
        MAX_JUMP_COUNT = 1;
        addSpriteSheet("bulletsheet", "assets/img/pills.png");
        addSpriteSheet("charsheet", "assets/img/khabanksprites.png");
        addSprite("stand", "charsheet",  18, 0, 129, 231, true);
        addSprite("stand", "charsheet",  159, 2, 160, 231, true);
        addSprite("bullet","objectsheet",  99, 34, 94, 34, true);
        addSprite("pill", "bulletsheet",  9, 35, 81, 85, true);
        addSprite("pill", "bulletsheet",  104, 60, 73, 64, true);
        addSprite("pill", "bulletsheet",  200, 30, 63, 94, true);
        addSprite("pill", "bulletsheet",  294, 47, 68, 68, true);
        addSprite("pill", "bulletsheet",  385, 38, 87, 86, true);
        Locator::getSoundEffectPlayer()->loadSoundEffect("bosshurt","assets/se/boss-hurt.wav");
        Locator::getSoundEffectPlayer()->loadSoundEffect("choido","assets/se/khabanhchoido.wav");
        Locator::getSoundEffectPlayer()->loadSoundEffect("vienthuockeo","assets/se/vienthuockeo.wav");
        Locator::getSoundEffectPlayer()->loadSoundEffect("vienthuocaxitb1","assets/se/vienthuocaxitb1.wav");
        Locator::getSoundEffectPlayer()->loadSoundEffect("vienthuockimcuong","assets/se/vienthuockimcuong.wav");
        Locator::getSoundEffectPlayer()->loadSoundEffect("vienthuocvuongliem","assets/se/vienthuocvuongliem.wav");
        mInvincibleTick = 200;
    } else {
        mWidth = 20;
        mHeight = 35;
        MAX_HP = 150;
        MAX_MP = 100;
        MAX_VEL_X = 800;
        ACCELERATION = 3000;
        GRAVITY = 2500;
        JUMP_VELOCITY = 1200;
        MAX_JUMP_COUNT = 1;
        addSpriteSheet("charsheet", "assets/img/allmovespriteblanc.png");
        addSprite("stand", "charsheet",  43, 29, 52, 75, true);
        addSprite("stand", "charsheet",  123, 30, 52, 75, true);
        addSprite("jump", "charsheet",  250, 30, 52, 75, true);
        addSprite("jump", "charsheet",  314, 28, 52, 75, true);
        addSprite("wallslide", "charsheet",  424, 39, 52, 75, true);
        addSprite("move", "charsheet",  44, 138, 52, 75, true);
        addSprite("move", "charsheet",  104, 133, 52, 75, true);
        addSprite("melee", "charsheet",  232, 145, 66, 68, true);
        addSprite("melee", "charsheet",  309, 147, 66, 68, true);
        addSprite("melee", "charsheet",  391, 149, 66, 68, true);
        addSprite("ranged", "charsheet",  89, 263, 82, 87, true);
        addSprite("ranged", "charsheet",  195, 269, 103, 81, true);
        addSprite("bullet","objectsheet",  99, 34, 94, 34, true);
        Locator::getSoundEffectPlayer()->loadSoundEffect("ranged","assets/se/gunshot.wav");
        Locator::getSoundEffectPlayer()->loadSoundEffect("melee","assets/se/knifeattack.wav");
    }
    addSprite("healthbg", "objectsheet", 166, 252, 288, 33);
    addSprite("healthbar", "objectsheet", 166, 301, 200, 12);
    mCharFont = TTF_OpenFont("assets/fonts/FVF Fernando 08.ttf", 12);
    mCurrentSprite = &mCharacterSprites["stand"][0];
    Locator::getSoundEffectPlayer()->loadSoundEffect("step","assets/se/step.wav");
    Locator::getSoundEffectPlayer()->loadSoundEffect("jump","assets/se/jump.wav");
    Locator::getSoundEffectPlayer()->loadSoundEffect("slide","assets/se/slide.wav");
    mHitPoints = MAX_HP;
    mJumpLeft = MAX_JUMP_COUNT;
    gGameInstance = gameInstance;
    gGameStateInstance = gameStateInstance;
    mCurrentState = new StandingState();
    mCurrentActionState = new DoNothingState();
}

void Character::addSpriteSheet(std::string name, std::string path) {
    mSpriteSheets.emplace(name, path);
}

void Character::addSprite(std::string type, std::string sheetName, int x, int y, int w, int h, bool defaultHitBox) {
    if (mSpriteSheets.count(sheetName))
        mCharacterSprites[type].emplace_back(&mSpriteSheets[sheetName], x, y, w, h, defaultHitBox);
}

int Character::getPosX() {
    return static_cast<int>(mPos.x);
}

int Character::getPosY() {
    return static_cast<int>(mPos.y);
}

Sprite* Character::getCurrentSprite() {
    return mCurrentSprite;
}

void Character::transferBullet(std::vector<std::unique_ptr<Bullet>>& bullets) {
      bullets.insert(bullets.end(),std::make_move_iterator(mCharacterBullets.begin()), std::make_move_iterator(mCharacterBullets.end()));
      mCharacterBullets.clear();
}

void Character::overrideBossState() {
    if(mCharName == "KhaBanh") {
        delete mCurrentState;
        mCurrentState = new KhaBanhState();
    }
}

void Character::setEnemyPos(Vector2D pos) {
    mEnemyPos = pos;
}

void Character::handleEvent(SDL_Event* e) {
    CharacterState* newState = mCurrentState->handleInput(*this, e);
    CharacterState* newActionState = mCurrentActionState->handleInput(*this, e);
    if (newState != nullptr) {
        delete mCurrentState;
        mCurrentState = newState;
    }
    if (newActionState != nullptr) {
        delete mCurrentActionState;
        mCurrentActionState = newActionState;
    }
}

void Character::handleLogic(std::vector<SDL_Rect>* solidObjects, double timeStep) {

    CharacterState* newState = mCurrentState->handleLogic(*this, solidObjects, timeStep);
    CharacterState* newActionState = mCurrentActionState->handleLogic(*this, solidObjects, timeStep);
    if (newState != nullptr) {
        delete mCurrentState;
        mCurrentState = newState;
    }
    if (newActionState != nullptr) {
        delete mCurrentActionState;
        mCurrentActionState = newActionState;
    }
    if(mCharInvincibleTimer.isStarted() && mCharInvincibleTimer.getTicks()>=static_cast<Uint32>(mInvincibleTick)) {
        mCharInvincibleTimer.stop();
    }
}

void Character::handleGraphics() {
    mCurrentState->handleGraphics(*this);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (mFacingDirection == LEFT) flip = SDL_FLIP_HORIZONTAL;
    SDL_Rect currentPos = Locator::getRenderer()->getAbsolutePosition(getCurrentSprite()->getTexture(), getPosX()-(getCurrentSprite()->getClip()->w-mWidth)/2, getPosY()-(getCurrentSprite()->getClip()->h-mHeight), getCurrentSprite()->getClip()->w, getCurrentSprite()->getClip()->h);
    if(mCharName == "KhaBanh") {
        if(mCharInvincibleTimer.isStarted()) {
            if(mCharInvincibleTimer.getTicks()/100%2 == 0) {
                Locator::getRenderer()->setTextureColor(getCurrentSprite()->getTexture(), 255, 150, 150);
            } else {
                Locator::getRenderer()->setTextureTransparency(getCurrentSprite()->getTexture(), 80);
            }
        }
    } else {
        if(mCharInvincibleTimer.isStarted()) {
            if(mCharInvincibleTimer.getTicks()/200%2 == 0) Locator::getRenderer()->setTextureTransparency(getCurrentSprite()->getTexture(), 100);
        }
    }

    Locator::getRenderer()->renderTexture(getCurrentSprite()->getTexture(), getCurrentSprite()->getClip(), &currentPos, flip);
    SDL_Rect solidBoxChar = Locator::getRenderer()->getAbsolutePosition(getCurrentSprite()->getTexture(), getPosX(), getPosY(), mWidth, mHeight);
    Locator::getRenderer()->renderRect(&solidBoxChar, 0 , 0, 255);

    Locator::getRenderer()->setTextureTransparency(getCurrentSprite()->getTexture(), 255);
    Locator::getRenderer()->setTextureColor(getCurrentSprite()->getTexture(),255,255,255);

}

void Character::move(double t, bool isFalling) {
    if (mMoveDirectionX == LEFT || mMoveDirectionX == RIGHT) {

        double normalizedAccelaration = ACCELERATION;
        double normalizedVelX = mVel.x;
        double normalizedMaxVelX = MAX_VEL_X;
        if (mMoveDirectionX == LEFT) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
            normalizedMaxVelX = -normalizedMaxVelX;
        }

        if(isFalling)
            normalizedAccelaration *= 0.6;

        if (normalizedVelX < 0)
            normalizedAccelaration *= 1.5;
        if (normalizedVelX >= MAX_VEL_X) {
            mPos.x += mVel.x * t;
            mVel.x = normalizedMaxVelX;
        } else {
            mPos.x += mVel.x * t;
            mVel.x += normalizedAccelaration * t;
            if (normalizedVelX >= MAX_VEL_X) mVel.x = normalizedMaxVelX;
        }
    } else if (mMoveDirectionX == NONE && mVel.x != 0) {

        double normalizedAccelaration = ACCELERATION;
        double normalizedVelX = mVel.x;

        if(isFalling)
            normalizedAccelaration *= 0.5;
        else 
            normalizedAccelaration *= 1.5;

        if (mVel.x > 0) {
            normalizedAccelaration = -normalizedAccelaration;
            normalizedVelX = -normalizedVelX;
        }
        mPos.x += mVel.x * t;
        mVel.x += normalizedAccelaration * t;
        if (normalizedVelX + normalizedAccelaration * t > 0)
            mVel.x = 0;
    }
}

void Character::jump() {
    if (mJumpLeft > 0) {
        --mJumpLeft;
        mVel.y = -JUMP_VELOCITY;
        Locator::getSoundEffectPlayer()->play("jump");
    }
}

void Character::directionalJump(Direction direction) {
    jump();
    if(direction == RIGHT) {
        mFacingDirection = RIGHT;
        mVel.x = 0.7*MAX_VEL_X;
    }
    else {
        mFacingDirection = LEFT;
        mVel.x = -0.7*MAX_VEL_X;
    }
    move(0.03, true);
}

void Character::decreaseHP(int HP) {
        if(!mCharInvincibleTimer.isStarted()) {
            if(mCharName=="KhaBanh") {
                Locator::getSoundEffectPlayer()->play("bosshurt");
            } else {
                Locator::getSoundEffectPlayer()->play("charhurt");
            }

            SDL_Haptic* controllerHaptic = gGameInstance->mControllerHaptic;
            if(controllerHaptic!=nullptr && mCharName!="KhaBanh") {
                SDL_HapticRumblePlay(controllerHaptic, 1.0, 400);
            }
            mHitPoints-=HP;
            if(mHitPoints <=0 ) {
                mHitPoints = 0;
            }
            mCharInvincibleTimer.start();
        }
    }

Character::~Character() {
    Locator::getSoundEffectPlayer()->free();
}

