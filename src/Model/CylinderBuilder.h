//
// Created by wojciech on 01.06.17.
//

#ifndef GLPRESS_CYLINDERBUILDER_H
#define GLPRESS_CYLINDERBUILDER_H

#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "Mesh.h"

class CylinderBuilder {
private:

    GLfloat mRadius;
    GLfloat mHeight;
    GLuint mSides;

    glm::vec2 mWrapBegin;
    glm::vec2 mWrapEnd;

    glm::vec2 mUpperCapBegin;
    glm::vec2 mUpperCapEnd;

    glm::vec2 mLowerCapBegin;
    glm::vec2 mLowerCapEnd;

public:
    CylinderBuilder() : mRadius(1.0f), mHeight(1.0f), mSides(24) { };

    CylinderBuilder& radius(GLfloat radius) {
        mRadius = radius;
        return *this;
    };

    CylinderBuilder& height(GLfloat height) {
        mHeight = height;
        return *this;
    };

    CylinderBuilder& sides(GLuint sides) {
        mSides = sides;
        return *this;
    };

    CylinderBuilder& wrap(glm::vec2 begin, glm::vec2 end) {
        mWrapBegin = begin;
        mWrapEnd = end;
        return *this;
    };

    CylinderBuilder& upperCap(glm::vec2 begin, glm::vec2 end) {
        mUpperCapBegin = begin;
        mUpperCapEnd = end;
        return *this;
    };

    CylinderBuilder& bottomCap(glm::vec2 begin, glm::vec2 end) {
        mLowerCapBegin = begin;
        mLowerCapEnd = end;
        return *this;
    };

    std::shared_ptr<Mesh> build();
};

#endif //GLPRESS_CYLINDERBUILDER_H
