//
// Created by wojciech on 30.04.17.
//

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, GLfloat angle, GLfloat intensity, GLfloat distance) : Light(Light::Type::SPOT) {
    mPosition = position;
    mDirection = direction;
    mDiffuse = color * intensity;

    mConstant = 1.0f;
    mLinear = 0.14;
    mQuadratic = 0.07;

    mCutOff = glm::cos(angle);
    mOuterCutOff = glm::cos(glm::radians(25.0f));
}

void SpotLight::setPosition(glm::vec3 position) {
    mPosition = position;
}

void SpotLight::setTarget(glm::vec3 target) {
    mDirection = glm::normalize(target - mPosition);
}
