#ifndef GLPRESS_ANIMATIONLIGHTINTENSITY_H
#define GLPRESS_ANIMATIONLIGHTINTENSITY_H


#include <memory>
#include "Animation.h"
#include "../Light/Light.h"

class AnimationLightIntensity :  public Animation {
private:
    std::shared_ptr<Light> mLight;
    GLfloat mDestination;
    GLfloat mBegin;
    GLfloat mStep;
public:
    AnimationLightIntensity(std::shared_ptr<Light> light, GLfloat duration, GLfloat destination) :
    Animation(duration), mLight(light), mDestination(destination) {}

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();

};


#endif //GLPRESS_ANIMATIONLIGHTINTENSITY_H
