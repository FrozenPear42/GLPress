#ifndef GLPRESS_PLANEBUILDER_H
#define GLPRESS_PLANEBUILDER_H

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include "Mesh.h"

class PlaneBuilder {
private:
    GLfloat mWidth;
    GLfloat mHeight;
    glm::vec2 mBegin;
    glm::vec2 mEnd;

public:
    PlaneBuilder() : mWidth(1), mHeight(1), mBegin(0, 0), mEnd(1, 1) {}
    PlaneBuilder& width(GLfloat w) {
        mWidth = w;
        return *this;
    }
    PlaneBuilder& height(GLfloat h) {
        mHeight = h;
        return *this;
    }

    PlaneBuilder& mapping(glm::vec2 begin, glm::vec2 end) {
        mBegin = begin;
        mEnd = end;
        return *this;
    }

    std::shared_ptr<Mesh> build();
};


#endif //GLPRESS_PLANEBUILDER_H
