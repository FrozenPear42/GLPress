#include "PlaneBuilder.h"

std::shared_ptr<Mesh> PlaneBuilder::build() {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices{0, 1, 2, 1, 3, 2};
    vertices.emplace_back(glm::vec3(-0.5 * mWidth, -0.5 * mHeight, 0), glm::vec3(0, 0, -1), glm::vec2(mBegin.x, mBegin.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth, -0.5 * mHeight, 0), glm::vec3(0, 0, -1), glm::vec2(mEnd.x, mBegin.y));
    vertices.emplace_back(glm::vec3(-0.5 * mWidth,  0.5 * mHeight, 0), glm::vec3(0, 0, -1), glm::vec2(mBegin.x, mEnd.y));
    vertices.emplace_back(glm::vec3( 0.5 * mWidth,  0.5 * mHeight, 0), glm::vec3(0, 0, -1), glm::vec2(mEnd.x, mEnd.y));

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));

}
