#include <glm/geometric.hpp>
#include "DirectLight.h"

DirectLight::DirectLight(glm::vec3 direction, glm::vec3 color, GLfloat intensity) : Light(Light::Type::DIRECT) {
    mDirection = direction;
    mDiffuse = color * intensity;
    mAmbient = glm::normalize(color) * 0.1f;
}
