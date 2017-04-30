//
// Created by wojciech on 30.04.17.
//

#ifndef GLPRESS_DIRECTLIGHT_H
#define GLPRESS_DIRECTLIGHT_H

#include "Light.h"

class DirectLight : public Light {
public:
    DirectLight(glm::vec3 direction, glm::vec3 color, GLfloat intensity);
};


#endif //GLPRESS_DIRECTLIGHT_H
