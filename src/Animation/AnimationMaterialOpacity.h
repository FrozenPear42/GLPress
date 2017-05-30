//
// Created by wojciech on 31.05.17.
//

#ifndef GLPRESS_ANIMATIONMATERIALOPACITY_H
#define GLPRESS_ANIMATIONMATERIALOPACITY_H


#include "Animation.h"
#include "../Material/Material.h"

class AnimationMaterialOpacity : public Animation {
private:
    std::shared_ptr<Material> mMaterial;
    GLfloat mDestination;
    GLfloat mBegin;
    GLfloat mStep;
public:
    AnimationMaterialOpacity(std::shared_ptr<Material>& material, GLfloat duration, GLfloat destination) :
            Animation(duration), mMaterial(material), mDestination(destination) {}

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();

};


#endif //GLPRESS_ANIMATIONMATERIALOPACITY_H
