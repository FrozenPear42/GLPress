//
// Created by wojciech on 29.05.17.
//

#include "ModelAnimationMove.h"


ModelAnimationMove::ModelAnimationMove(std::shared_ptr<Model> model, glm::vec3 begin, glm::vec3 end, GLfloat duration) :
        Animation(duration), mModel(model), mBegin(begin), mEnd(end) {
    mStep = (mEnd - mBegin) / mDuration;
}

void ModelAnimationMove::animationStep(GLfloat delta) {
    if (mRunning) {
        mTimeLeft -= delta;
        if (mTimeLeft <= 0) {
            mTimeLeft = 0;
            mModel->setPosition(mEnd);
            mRunning = false;
        } else {
            mModel->setPosition(mModel->getPosition() + mStep * delta);
        }
    }
}

void ModelAnimationMove::animationReset() {
    Animation::animationReset();
}
