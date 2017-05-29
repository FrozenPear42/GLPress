//
// Created by wojciech on 29.05.17.
//

#ifndef GLPRESS_ANIMATIONSEQUENCE_H
#define GLPRESS_ANIMATIONSEQUENCE_H


#include <memory>
#include <vector>
#include "Animation.h"

class AnimationSequence : public Animation {
private:
    std::vector<std::unique_ptr<Animation>> mAnimations;
    std::size_t mCurrentAnimation;
public:
    AnimationSequence() : Animation(0), mCurrentAnimation(0) {}

    void addToSequence(std::unique_ptr<Animation>&& animation);

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();

};


#endif //GLPRESS_ANIMATIONSEQUENCE_H
