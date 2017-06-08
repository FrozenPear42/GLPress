//
// Created by wojciech on 30.04.17.
//

#ifndef GLPRESS_POINTLIGHT_H
#define GLPRESS_POINTLIGHT_H

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include "Light.h"

class PointLight : public Light {
public:
    PointLight(glm::vec3 position, GLfloat intensity, glm::vec3 color) :
            Light(Type::POINT, intensity, color) {
        mPosition = position;
        mConstant = 1.0f;
        mLinear = 0.14f;
        mQuadratic = 0.07f;
    }

    void setPosition(glm::vec3 position) {
        mPosition = position;
    }

    glm::vec3 getPosition() const {
        return mPosition;
    }

};

#endif //GLPRESS_POINTLIGHT_H
