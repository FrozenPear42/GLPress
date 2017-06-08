//
// Created by wojciech on 03.06.17.
//

#include "AnimationRotateBy.h"

void AnimationRotateBy::animationStart() {
    Animation::animationStart();
    mBegin = mModel->getRotation();
    mEnd = mModel->getRotation() + mDelta;
    mStep = mDelta/mDuration;
}

bool AnimationRotateBy::animationStep(GLfloat delta) {
    if (mRunning) {
        mTimeLeft -= delta;
        if (mTimeLeft <= 0) {
            mTimeLeft = 0;
            mModel->setRotation(mEnd);
            mRunning = false;
            return true;
        } else {
            mModel->setRotation(mModel->getRotation() + mStep * delta);
            return false;
        }
    }
    return true;
}

void AnimationRotateBy::animationReset() {
    Animation::animationReset();
    mModel->setRotation(mBegin);
}
