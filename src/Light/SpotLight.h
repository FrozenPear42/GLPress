#ifndef GLPRESS_SPOTLIGHT_H
#define GLPRESS_SPOTLIGHT_H

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, GLfloat distance, GLfloat angle, GLfloat intensity, glm::vec3 color) :
            Light(Type::SPOT, intensity, color) {
        mPosition = position;
        mDirection = direction;
        mConstant = 1.0f;
        mLinear = 0.14f;
        mQuadratic = 0.07f;
        mCutOff = glm::cos(angle);
        mOuterCutOff = glm::cos(glm::radians(25.0f));
    }

    void setPosition(glm::vec3 position) {
        mPosition = position;
    }

    void setTarget(glm::vec3 target) {
        mDirection = glm::normalize(target - mPosition);
    }

};


#endif //GLPRESS_SPOTLIGHT_H
