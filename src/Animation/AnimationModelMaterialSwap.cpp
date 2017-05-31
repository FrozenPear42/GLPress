//
// Created by wojciech on 31.05.17.
//

#include "AnimationModelMaterialSwap.h"

void AnimationModelMaterialSwap::animationStart() {
    Animation::animationStart();
    mBaseMaterial = mModel->getMaterial();
    mModel->setMaterial(mMaterial);
}

bool AnimationModelMaterialSwap::animationStep(GLfloat delta) {
    return true;
}

void AnimationModelMaterialSwap::animationReset() {
    Animation::animationReset();
    mModel->setMaterial(mBaseMaterial);
}
