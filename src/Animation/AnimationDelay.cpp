//
// Created by wojciech on 30.05.17.
//

#include "AnimationDelay.h"

bool AnimationDelay::animationStep(GLfloat delta) {
    if (mRunning) {
        mTimeLeft -= delta;
        if (mTimeLeft <= 0) {
            mTimeLeft = 0;
            mRunning = false;
            return true;
        } else {
            return false;
        }
    }
    return true;
}
