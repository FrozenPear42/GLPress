//
// Created by wojciech on 30.05.17.
//

#ifndef GLPRESS_ANIMATIONDELAY_H
#define GLPRESS_ANIMATIONDELAY_H


#include "Animation.h"

class AnimationDelay : public Animation {
private:

public:
    AnimationDelay(GLfloat delay) : Animation(delay) {}

    virtual bool animationStep(GLfloat delta);
};


#endif //GLPRESS_ANIMATIONDELAY_H
