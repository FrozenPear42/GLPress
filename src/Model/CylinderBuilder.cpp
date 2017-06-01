#include <glm/gtc/constants.hpp>
#include <cmath>
#include <glm/geometric.hpp>
#include "CylinderBuilder.h"

std::shared_ptr<Mesh> CylinderBuilder::build() {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    float deltaAngle = glm::two_pi<float>() / mSides;

    GLfloat deltaU = (mWrapEnd.x - mWrapBegin.x)/mSides;


    for (GLuint i = 0; i <= mSides; ++i) {
        float x = mRadius * std::cos(deltaAngle * i);
        float y = mRadius * std::sin(deltaAngle * i);

        vertices.emplace_back(glm::vec3(x, y, -mHeight / 2), glm::normalize(glm::vec3(x, y, 0)), mWrapBegin.x + glm::vec2(i * deltaU, mWrapBegin.y));
        vertices.emplace_back(glm::vec3(x, y,  mHeight / 2), glm::normalize(glm::vec3(x, y, 0)), mWrapBegin.x + glm::vec2(i * deltaU, mWrapEnd.y));
    }

    for (GLuint i = 0; i < 2 * mSides - 1; ++i) {
        indices.emplace_back(2 * ((i + 1) / 2));
        indices.emplace_back(i + 2);
        indices.emplace_back(2 * ((i + 1) / 2) + 1);

        indices.emplace_back(2 * ((i + 2) / 2));
        indices.emplace_back(i + 3);
        indices.emplace_back(2 * ((i + 1) / 2) + 1);
    }

    // Caps
    GLuint centerIdx = (GLuint) vertices.size();
    vertices.emplace_back(glm::vec3(0, 0, -mHeight / 2), glm::vec3(0, 0, -1), glm::vec2(0.5, 0.5));
    for (GLuint i = 0; i <= mSides; ++i) {
        float x = mRadius * std::cos(deltaAngle * i);
        float y = mRadius * std::sin(deltaAngle * i);

        vertices.emplace_back(glm::vec3(x, y, -mHeight / 2), glm::vec3(0, 0, -1),
                              glm::vec2((x / mRadius + 1) / 2, (y / mRadius + 1) / 2));
    }

    for (GLuint i = 1; i < mSides + 1; ++i) {
        indices.emplace_back(centerIdx);
        indices.emplace_back(centerIdx + i);
        indices.emplace_back(centerIdx + i + 1);
    }

    centerIdx = (GLuint) vertices.size();
    vertices.emplace_back(glm::vec3(0, 0, mHeight / 2), glm::vec3(0, 0, 1), glm::vec2(0.5, 0.5));
    for (GLuint i = 0; i <= mSides; ++i) {
        float x = mRadius * std::cos(deltaAngle * i);
        float y = mRadius * std::sin(deltaAngle * i);

        vertices.emplace_back(glm::vec3(x, y, mHeight / 2), glm::vec3(0, 0, 1), glm::vec2((-x / mRadius + 1) / 2, (y / mRadius + 1) / 2));
    }

    for (GLuint i = 1; i < mSides + 1; ++i) {
        indices.emplace_back(centerIdx);
        indices.emplace_back(centerIdx + i);
        indices.emplace_back(centerIdx + i + 1);
    }


    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}
