#ifndef GLPRESS_ANIMATION_H
#define GLPRESS_ANIMATION_H

#include <bits/shared_ptr.h>
#include <GL/glew.h>

class Animation {
    friend class Model;

protected:
    GLfloat mDuration;
    GLfloat mTimeLeft;
    bool mRunning;

    Animation(GLfloat duration) : mDuration(duration), mTimeLeft(duration), mRunning(false) {}

public:
    virtual bool animationStep(GLfloat delta) = 0;

    virtual void animationReset() {
        mTimeLeft = mDuration;
        mRunning = false;
    };

    virtual void animationStart() { mRunning = true; }

    virtual void animationStop() { mRunning = false; }

    GLfloat getDuration() { return mDuration; };
};


#endif //GLPRESS_ANIMATION_H
