#ifndef GLPRESS_MODELANIMATIONMOVE_H
#define GLPRESS_MODELANIMATIONMOVE_H


#include <glm/vec3.hpp>
#include "../Model/Model.h"
#include "Animation.h"

class AnimationMoveBy : public Animation {
private:
    std::shared_ptr<Model> mModel;
    glm::vec3 mBegin;
    glm::vec3 mEnd;
    glm::vec3 mDelta;
    glm::vec3 mStep;

public:
    AnimationMoveBy(std::shared_ptr<Model> model, glm::vec3 delta, GLfloat duration);

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();

};


#endif //GLPRESS_MODELANIMATIONMOVE_H
