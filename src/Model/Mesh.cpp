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

std::shared_ptr<Mesh> Mesh::loadFromObjFile(std::string fileName) {
    std::ifstream file(fileName.c_str());


    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textCoords;

    std::vector<Vertex> resVertices;
    std::vector<GLuint> resIndices;

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream data(line);
        std::string actionToken;
        data >> actionToken;
        if (actionToken == "v") {
            double x, y, z;
            data >> x >> y >> z;
            vertices.emplace_back(x, y, z);
            Logger::info("Vertex");
        } else if (actionToken == "vn") {
            double x, y, z;
            data >> x >> y >> z;
            normals.emplace_back(x, y, z);
            Logger::info("Normal");
        } else if (actionToken == "vt") {
            double u, v;
            data >> u >> v;
            textCoords.emplace_back(u, v);
            Logger::info("Texture");
        } else if (actionToken == "f") {
            std::string values;
            std::string item;
            GLuint v, n, t;
            GLuint pos;

            while (data >> values) {
                pos = (GLuint) values.find("/", 0);
                item = values.substr(0, pos);
                v = (GLuint) std::stoi(item) - 1;

                values = values.substr(pos + 1);
                pos = (GLuint) values.find("/", 0);
                item = values.substr(0, pos);
                t = (GLuint) std::stoi(item) - 1;

                values = values.substr(pos + 1);
                pos = (GLuint) values.find("/", 0);
                item = values.substr(0, pos);
                n = (GLuint) std::stoi(item) - 1;
 
                Logger::info("Vert " + std::to_string(v) + " " + std::to_string(n) + " " + std::to_string(t));

                auto idx = std::find_if(resVertices.begin(), resVertices.end(), [&](const Vertex& vertex) -> bool {
                    return vertex.position == vertices[v] && vertex.textCoord == textCoords[t];
                });

                if (idx == resVertices.end()) {
                    resVertices.emplace_back(vertices[v], textCoords[t]);
                    resIndices.emplace_back(resVertices.size() - 1);
                } else {
                    resIndices.emplace_back(idx - resVertices.begin());
                }
            }
        } else if (actionToken[0] == '#') {
            std::string comment;
            data >> comment;
            Logger::info("Comment: " + comment);
        }
    }
    return std::make_shared<Mesh>(std::move(resVertices), std::move(resIndices));
}