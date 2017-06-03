//
// Created by wojciech on 30.04.17.
//

#ifndef GLPRESS_DIRECTLIGHT_H
#define GLPRESS_DIRECTLIGHT_H

#include "Light.h"

class DirectLight : public Light {
public:
    DirectLight(glm::vec3 direction, GLfloat intensity, glm::vec3 color) :
            Light(Type::DIRECT, intensity, color) {
        mDirection = direction;
    }
};


#endif //GLPRESS_DIRECTLIGHT_H
