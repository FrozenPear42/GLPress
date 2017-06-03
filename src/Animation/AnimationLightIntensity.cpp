//
// Created by wojciech on 03.06.17.
//

#include "AnimationLightIntensity.h"

void AnimationLightIntensity::animationStart() {
    Animation::animationStart();
    mBegin = mLight->getIntensity();
    mStep = (mDestination - mBegin) / mDuration;
}

void AnimationLightIntensity::animationReset() {
    Animation::animationReset();
    mLight->setIntensity(mBegin);
}

bool AnimationLightIntensity::animationStep(GLfloat delta) {
    if (mRunning) {
        mTimeLeft -= delta;
        if (mTimeLeft <= 0) {
            mTimeLeft = 0;
            mLight->setIntensity(mDestination);
            mRunning = false;
            return true;
        } else {
            mLight->setIntensity(mLight->getIntensity() + mStep * delta);
            return false;
        }
    }
    return true;
}


