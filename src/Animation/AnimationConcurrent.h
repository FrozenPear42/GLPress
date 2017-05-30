//
// Created by wojciech on 30.05.17.
//

#ifndef GLPRESS_ANIMATIONCONCURRENT_H
#define GLPRESS_ANIMATIONCONCURRENT_H


#include <vector>
#include <bits/shared_ptr.h>
#include <bits/unique_ptr.h>
#include "Animation.h"

class AnimationConcurrent : public Animation {
private:
    std::vector<std::shared_ptr<Animation>> mAnimations;
public:
    AnimationConcurrent() : Animation(0) {}

    void addAnimation(std::unique_ptr<Animation>&& animation);

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();

};


#endif //GLPRESS_ANIMATIONCONCURRENT_H
