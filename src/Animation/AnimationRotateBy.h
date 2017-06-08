#ifndef GLPRESS_ANIMATIONROTATEBY_H
#define GLPRESS_ANIMATIONROTATEBY_H


#include <glm/vec3.hpp>
#include <memory>
#include "Animation.h"
#include "../Model/Model.h"

class AnimationRotateBy : public Animation {
private:
    std::shared_ptr<Model> mModel;
    glm::vec3 mBegin;
    glm::vec3 mEnd;
    glm::vec3 mDelta;
    glm::vec3 mStep;

public:
    AnimationRotateBy(std::shared_ptr<Model> model, glm::vec3 delta, GLfloat duration) :
            Animation(duration), mModel(model), mDelta(delta) { };

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();

};

#endif //GLPRESS_ANIMATIONROTATEBY_H
