//
// Created by wojciech on 02.06.17.
//

#include "AnimationTextureDisplacement.h"

void AnimationTextureDisplacement::animationStart() {
    Animation::animationStart();
    mDelta = mTarget / mDuration;
    mBegin = mMaterial->getTextureDisplacement();
}

bool AnimationTextureDisplacement::animationStep(GLfloat delta) {
    if (mRunning) {
        mTimeLeft -= delta;
        if (mTimeLeft <= 0) {
            mTimeLeft = 0;
            mMaterial->setTextureDisplacement(mBegin + mTarget);
            mRunning = false;
            return true;
        } else {
            mMaterial->setTextureDisplacement(mMaterial->getTextureDisplacement() + mDelta * delta);
            return false;
        }
    }
    return true;
}

void AnimationTextureDisplacement::animationReset() {
    Animation::animationReset();
    mMaterial->setTextureDisplacement(mBegin);
}

