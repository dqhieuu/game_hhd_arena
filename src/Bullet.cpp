#include "Bullet.h"

Bullet::Bullet(int x, int y) {
    mPos.x = x;
    mPos.y = y;
    mIsActive = false;
    mIsDestroyed = false;
}

void Bullet::start() {
    if(!mIsActive && !mIsDestroyed) {
        mIsActive = true;
        mTimer.start();
    }
}

void Bullet::destroy() {
    if(!mIsDestroyed) {
        mIsActive = false;
        mIsDestroyed = true;
    }
}

