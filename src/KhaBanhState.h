#ifndef KHA_BANH_STATE_H
#define KHA_BANH_STATE_H

#include "Character.h"
#include "CharacterState.h"

class KhaBanhState : public CharacterState {
    public:
    KhaBanhState() {mCharStateTimer.start();}
    virtual CharacterState* handleInput(Character& character, SDL_Event* e);
    virtual CharacterState* handleLogic(Character& character, std::vector<SDL_Rect>* solidObjects, double t);
    virtual void handleGraphics(Character& character);
    bool mIsDoingAction;
    int mActionState=0;
    Timer mActionTimer;
    double mMoveDeg;
    Vector2D mMoveVect;
    Vector2D mMoveDest;
    bool mHasShot = false;
    bool mHasSaidPill = false;
    int mStatePhase;
    int mStatePosMoved=0;
    int mStateShootFired=0;
};

#endif