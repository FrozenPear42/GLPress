//
// Created by wojciech on 01.06.17.
//

#ifndef GLPRESS_CUBEBUILDER_H
#define GLPRESS_CUBEBUILDER_H

#include <glm/vec2.hpp>
#include "Mesh.h"

class CubeBuilder {
private:
    GLfloat mWidth;
    GLfloat mHeight;
    GLfloat mDepth;

    glm::vec2 mFrontBegin;
    glm::vec2 mFrontEnd;

    glm::vec2 mBackBegin;
    glm::vec2 mBackEnd;

    glm::vec2 mTopBegin;
    glm::vec2 mTopEnd;

    glm::vec2 mBottomBegin;
    glm::vec2 mBottomEnd;

    glm::vec2 mLeftBegin;
    glm::vec2 mLeftEnd;

    glm::vec2 mRightBegin;
    glm::vec2 mRightEnd;

public:
    CubeBuilder() : mWidth(1), mHeight(1), mDepth(1) {};

    CubeBuilder& width(GLfloat w) {
        mWidth = w;
        return *this;
    };

    CubeBuilder& height(GLfloat h) {
        mHeight = h;
        return *this;
    };

    CubeBuilder& depth(GLfloat d) {
        mDepth = d;
        return *this;
    }

    CubeBuilder& frontMap(glm::vec2 begin, glm::vec2 end) {
        mFrontBegin = begin;
        mFrontEnd = end;
        return *this;
    }
    CubeBuilder& backMap(glm::vec2 begin, glm::vec2 end) {
        mBackBegin = begin;
        mBackEnd = end;
        return *this;
    }

    CubeBuilder& topMap(glm::vec2 begin, glm::vec2 end) {
        mTopBegin = begin;
        mTopEnd = end;
        return *this;
    }
    CubeBuilder& bottomMap(glm::vec2 begin, glm::vec2 end) {
        mBottomBegin = begin;
        mBottomEnd = end;
        return *this;
    }
    CubeBuilder& leftMap(glm::vec2 begin, glm::vec2 end) {
        mLeftBegin = begin;
        mLeftEnd = end;
        return *this;
    }
    CubeBuilder& rightMap(glm::vec2 begin, glm::vec2 end) {
        mRightBegin = begin;
        mRightEnd = end;
        return *this;
    }

    std::shared_ptr<Mesh> build();


};


#endif //GLPRESS_CUBEBUILDER_H
