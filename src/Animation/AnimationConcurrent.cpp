//
// Created by wojciech on 30.05.17.
//

#include "AnimationConcurrent.h"

void AnimationConcurrent::addAnimation(std::unique_ptr<Animation>&& animation) {
    mAnimations.emplace_back(animation);
    mDuration = std::max(animation->getDuration(), mDuration);
}

void AnimationConcurrent::animationStart() {
    Animation::animationStart();
    for (auto&& anim : mAnimations)
        anim->animationStart();
}

bool AnimationConcurrent::animationStep(GLfloat delta) {
    bool finished = true;
    for (auto&& anim : mAnimations)
        if (!anim->animationStep(delta))
            finished = false;
    return finished;
}

void AnimationConcurrent::animationReset() {
    for(auto&& anim : mAnimations)
        anim->animationReset();
}
