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
    PointLight(glm::vec3 position, glm::vec3 color, GLfloat intensity, GLfloat distance);
    void setPosition(glm::vec3 position);
};

#endif //GLPRESS_POINTLIGHT_H
