#ifndef GLPRESS_ANIMATIONTEXTUREDISPLACEMENT_H
#define GLPRESS_ANIMATIONTEXTUREDISPLACEMENT_H


#include "Animation.h"
#include "../Material/Material.h"

class AnimationTextureDisplacement : public Animation {
private:
    std::shared_ptr<Material> mMaterial;
    glm::vec2 mDelta;
    glm::vec2 mBegin;
    glm::vec2 mTarget;
public:
    AnimationTextureDisplacement(std::shared_ptr<Material> material, glm::vec2 delta, GLfloat duration) :
            Animation(duration), mMaterial(material), mTarget(delta) { }

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();
};


#endif //GLPRESS_ANIMATIONTEXTUREDISPLACEMENT_H
