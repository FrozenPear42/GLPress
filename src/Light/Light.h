#ifndef GLPRESS_LIGHT_H
#define GLPRESS_LIGHT_H


#include <glm/vec3.hpp>
#include <GL/glew.h>

class Light {
    friend class Renderer;

public:
    enum class Type {
        DIRECT, POINT, SPOT
    };

    Type getType();

protected:
    Light(Type type) : mType(type) {}

    Type mType;

    glm::vec3 mDirection;
    glm::vec3 mPosition;

    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;

    GLfloat mCutOff;
    GLfloat mOuterCutOff;

    GLfloat mConstant;
    GLfloat mLinear;
    GLfloat mQuadratic;

};


#endif //GLPRESS_LIGHT_H
