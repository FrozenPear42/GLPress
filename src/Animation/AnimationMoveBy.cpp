//
// Created by wojciech on 29.05.17.
//

#include "AnimationMoveBy.h"


AnimationMoveBy::AnimationMoveBy(std::shared_ptr<Model> model, glm::vec3 delta, GLfloat duration) :
        Animation(duration), mModel(model), mDelta(delta) {}

bool AnimationMoveBy::animationStep(GLfloat delta) {
    if (mRunning) {
        mTimeLeft -= delta;
        if (mTimeLeft <= 0) {
            mTimeLeft = 0;
            mModel->setPosition(mEnd);
            mRunning = false;
            return true;
        } else {
            mModel->setPosition(mModel->getPosition() + mStep * delta);
            return false;
        }
    }
    return true;
}

void AnimationMoveBy::animationReset() {
    Animation::animationReset();
    mModel->setPosition(mBegin);
}

void AnimationMoveBy::animationStart() {
    Animation::animationStart();
    mBegin = mModel->getPosition();
    mEnd = mBegin + mDelta;
    mStep = mDelta / mDuration;
}
