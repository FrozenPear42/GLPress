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

    Type getType() const { return mType; };

    GLfloat getIntensity() const { return mIntensity; }

    void setIntensity(GLfloat intensity) {
        mIntensity = intensity;
        mDiffuse = mColor * mIntensity;
    };



protected:
    Light(Type type, GLfloat intensity, glm::vec3 color  = glm::vec3(1,1,1)) :
            mType(type), mIntensity(intensity), mColor(color), mDiffuse(mColor * mIntensity) {}

    Type mType;

    GLfloat mIntensity;
    glm::vec3 mColor;

    glm::vec3 mDirection;
    glm::vec3 mPosition;

    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;

    GLfloat mCutOff;
    GLfloat mOuterCutOff;

    GLfloat mConstant;
    GLfloat mLinear;
    GLfloat mQuadratic;

};


#endif //GLPRESS_LIGHT_H
