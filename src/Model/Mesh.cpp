#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<GLuint>&& indices) : mVertices(vertices), mIndices(indices) {
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), &mIndices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);
    // Texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, textCoord));

    glBindVertexArray(0);
}

void Mesh::draw() {
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, (GLsizei) mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

std::shared_ptr<Mesh> Mesh::loadFromFile(std::string fileName) {
    GLuint verticesCount;
    GLuint indicesCount;

    std::ifstream file(fileName.c_str());
    file >> verticesCount >> indicesCount;

    if (file.bad())
        throw std::runtime_error("Error reading mesh file");

    std::cout << "File: " << fileName << "\n";
    std::cout << "Verts: " << verticesCount << "\n";
    std::cout << "Indices: " << indicesCount << "\n";

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    for (GLuint i = 0; i < verticesCount; ++i) {
        float data[5];
        file >> data[0] >> data[1] >> data[2] >> data[3] >> data[4];
        vertices.emplace_back(glm::vec3(data[0], data[1], data[2]), glm::vec2(data[3], data[4]));
    }

    for (GLuint i = 0; i < indicesCount; ++i) {
        float data;
        file >> data;
        indices.emplace_back(data);
    }

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}
