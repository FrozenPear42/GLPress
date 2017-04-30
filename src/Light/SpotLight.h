#ifndef GLPRESS_SPOTLIGHT_H
#define GLPRESS_SPOTLIGHT_H

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include "Light.h"

class SpotLight : public Light  {
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, GLfloat angle, GLfloat intensity, GLfloat distance);
    void setPosition(glm::vec3 position);
    void setTarget(glm::vec3 target);
};


#endif //GLPRESS_SPOTLIGHT_H
