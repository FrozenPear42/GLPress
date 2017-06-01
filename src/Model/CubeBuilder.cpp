#include "CubeBuilder.h"

std::shared_ptr<Mesh> CubeBuilder::build() {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices{ 0,  1,  2,
                                 2,  1,  3,
                                 4,  5,  6,
                                 6,  5,  7,
                                 8,  9, 10,
                                 10,  9, 11,
                                 12, 13, 14,
                                 14, 13, 15,
                                 16, 17, 18,
                                 18, 17, 19,
                                 20, 21, 22,
                                 22, 21, 23,};

    vertices.emplace_back(glm::vec3(-0.5 * mWidth, -0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0,  0,  1), glm::vec2(mFrontBegin.x, mFrontBegin.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth, -0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0,  0,  1), glm::vec2(mFrontEnd.x, mFrontBegin.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth,  0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0,  0,  1), glm::vec2(mFrontBegin.x, mFrontEnd.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth,  0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0,  0,  1), glm::vec2(mFrontEnd.x, mFrontEnd.y));

    vertices.emplace_back(glm::vec3(-0.5 * mWidth,  0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0,  0, -1), glm::vec2(mBackEnd.x, mBackEnd.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth,  0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0,  0, -1), glm::vec2(mBackBegin.x, mBackEnd.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth, -0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0,  0, -1), glm::vec2(mBackEnd.x, mBackBegin.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth, -0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0,  0, -1), glm::vec2(mBackBegin.x, mBackBegin.y));

    vertices.emplace_back(glm::vec3(-0.5 * mWidth,  0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0,  1,  0), glm::vec2(mTopBegin.x, mTopBegin.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth,  0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0,  1,  0), glm::vec2(mTopEnd.x, mTopBegin.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth,  0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0,  1,  0), glm::vec2(mTopBegin.x, mTopEnd.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth,  0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0,  1,  0), glm::vec2(mTopEnd.x, mTopEnd.y));

    vertices.emplace_back(glm::vec3(-0.5 * mWidth, -0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0, -1,  0), glm::vec2(mBottomBegin.x, mBottomBegin.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth, -0.5 * mHeight, -0.5 * mDepth), glm::vec3( 0, -1,  0), glm::vec2(mBottomEnd.x, mBottomBegin.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth, -0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0, -1,  0), glm::vec2(mBottomBegin.x, mBottomEnd.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth, -0.5 * mHeight,  0.5 * mDepth), glm::vec3( 0, -1,  0), glm::vec2(mBottomEnd.x, mBottomEnd.y));

    vertices.emplace_back(glm::vec3( 0.5 * mWidth, -0.5 * mHeight,  0.5 * mDepth), glm::vec3( 1,  0,  0), glm::vec2(mRightBegin.x, mRightBegin.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth, -0.5 * mHeight, -0.5 * mDepth), glm::vec3( 1,  0,  0), glm::vec2(mRightEnd.x, mRightBegin.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth,  0.5 * mHeight,  0.5 * mDepth), glm::vec3( 1,  0,  0), glm::vec2(mRightBegin.x, mRightEnd.y));
    vertices.emplace_back(glm::vec3 (0.5 * mWidth,  0.5 * mHeight, -0.5 * mDepth), glm::vec3( 1,  0,  0), glm::vec2(mRightEnd.x, mRightEnd.y));

    vertices.emplace_back(glm::vec3(-0.5 * mWidth, -0.5 * mHeight, -0.5 * mDepth), glm::vec3(-1,  0,  0), glm::vec2(mLeftBegin.x, mLeftBegin.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth, -0.5 * mHeight,  0.5 * mDepth), glm::vec3(-1,  0,  0), glm::vec2(mLeftEnd.x, mLeftBegin.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth,  0.5 * mHeight, -0.5 * mDepth), glm::vec3(-1,  0,  0), glm::vec2(mLeftBegin.x, mLeftEnd.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth,  0.5 * mHeight,  0.5 * mDepth), glm::vec3(-1,  0,  0), glm::vec2(mLeftEnd.x, mLeftEnd.y));

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}
