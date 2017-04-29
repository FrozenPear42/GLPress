#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Mesh.h"
#include "../Utils/Logger.h"

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

