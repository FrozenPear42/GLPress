#ifndef GLPRESS_MODELANIMATIONMOVE_H
#define GLPRESS_MODELANIMATIONMOVE_H


#include <glm/vec3.hpp>
#include "../Model/Model.h"
#include "Animation.h"

class ModelAnimationMove : public Animation {
private:
    std::shared_ptr<Model> mModel;
    glm::vec3 mBegin;
    glm::vec3 mEnd;
    glm::vec3 mStep;

public:
    ModelAnimationMove(std::shared_ptr<Model> model, glm::vec3 begin, glm::vec3 end, GLfloat duration);

    virtual void animationStep(GLfloat delta);

    virtual void animationReset();

};


#endif //GLPRESS_MODELANIMATIONMOVE_H
