//
// Created by wojciech on 30.05.17.
//

#include "AnimationConcurrent.h"

void AnimationConcurrent::addAnimation(std::shared_ptr<Animation>&& animation) {
    mDuration = std::max(animation->getDuration(), mDuration);
    mAnimations.emplace_back(std::move(animation));
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
