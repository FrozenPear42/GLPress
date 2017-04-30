#include <glm/geometric.hpp>
#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, GLfloat intensity, GLfloat distance) : Light(
        Light::Type::POINT) {
    mPosition = position;
    mDiffuse = color * intensity;
    mAmbient = glm::normalize(color) * 0.1f;
    mConstant = 1.0f;
    mLinear = 0.14;
    mQuadratic = 0.07;
}

void PointLight::setPosition(glm::vec3 position) {
    mPosition = position;
}
