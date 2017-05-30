//
// Created by wojciech on 31.05.17.
//

#include "AnimationMaterialOpacity.h"

void AnimationMaterialOpacity::animationStart() {
    Animation::animationStart();
    mBegin = mMaterial->getOpacity();
    mStep = (mDestination - mBegin) / mDuration;
}

bool AnimationMaterialOpacity::animationStep(GLfloat delta) {
    if (mRunning) {
        mTimeLeft -= delta;
        if (mTimeLeft <= 0) {
            mTimeLeft = 0;
            mMaterial->setOpacity(mDestination);
            mRunning = false;
            return true;
        } else {
            mMaterial->setOpacity(mMaterial->getOpacity() + mStep * delta);
            return false;
        }
    }
    return true;
}

void AnimationMaterialOpacity::animationReset() {
    Animation::animationReset();
    mMaterial->setOpacity(mBegin);
}
