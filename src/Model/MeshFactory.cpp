#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <glm/gtc/constants.hpp>
#include <cmath>
#include <glm/geometric.hpp>
#include "MeshFactory.h"
#include "../Utils/Logger.h"

std::shared_ptr<Mesh> MeshFactory::createPlane(GLfloat w, GLfloat d, GLfloat uScale, GLfloat vScale) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices{0, 1, 2, 1, 3, 2};
    vertices.emplace_back(glm::vec3(-0.5 * w, -0.5 * d, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3( 0.5 * w, -0.5 * d, 0), glm::vec3(0, 0, 1), glm::vec2(uScale, 0));
    vertices.emplace_back(glm::vec3(-0.5 * w,  0.5 * d, 0), glm::vec3(0, 0, 1), glm::vec2(0, vScale));
    vertices.emplace_back(glm::vec3( 0.5 * w,  0.5 * d, 0), glm::vec3(0, 0, 1), glm::vec2(uScale, vScale));

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}

std::shared_ptr<Mesh> MeshFactory::createPlane(GLfloat w, GLfloat d) {
    return createPlane(w, d, 1, 1);
}


std::shared_ptr<Mesh> MeshFactory::createCube(GLfloat w, GLfloat h, GLfloat d,
                                              GLfloat suScale, GLfloat svScale,
                                              GLfloat cuScale, GLfloat cvScale) {

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

    GLfloat fU = 1.0f;
    GLfloat fV = 1.0f;
    GLfloat bU = 1.0f;
    GLfloat bV = 1.0f;
    GLfloat tU = 1.0f;
    GLfloat tV = 1.0f;
    GLfloat btU = 1.0f;
    GLfloat btV = 1.0f;
    GLfloat rU = 1.0f;
    GLfloat rV = 1.0f;
    GLfloat lU = 1.0f;
    GLfloat lV = 1.0f;

    vertices.emplace_back(glm::vec3(-0.5 * w, -0.5 * h,  0.5 * d), glm::vec3( 0,  0,  1), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3( 0.5 * w, -0.5 * h,  0.5 * d), glm::vec3( 0,  0,  1), glm::vec2(fU, 0));
    vertices.emplace_back(glm::vec3(-0.5 * w,  0.5 * h,  0.5 * d), glm::vec3( 0,  0,  1), glm::vec2(0, fV));
    vertices.emplace_back(glm::vec3( 0.5 * w,  0.5 * h,  0.5 * d), glm::vec3( 0,  0,  1), glm::vec2(fU, fV));

    vertices.emplace_back(glm::vec3(-0.5 * w,  0.5 * h, -0.5 * d), glm::vec3( 0,  0, -1), glm::vec2(bU, bV));
    vertices.emplace_back(glm::vec3( 0.5 * w,  0.5 * h, -0.5 * d), glm::vec3( 0,  0, -1), glm::vec2(0, bV));
    vertices.emplace_back(glm::vec3(-0.5 * w, -0.5 * h, -0.5 * d), glm::vec3( 0,  0, -1), glm::vec2(bU, 0));
    vertices.emplace_back(glm::vec3( 0.5 * w, -0.5 * h, -0.5 * d), glm::vec3( 0,  0, -1), glm::vec2(0, 0));

    vertices.emplace_back(glm::vec3(-0.5 * w,  0.5 * h,  0.5 * d), glm::vec3( 0,  1,  0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3( 0.5 * w,  0.5 * h,  0.5 * d), glm::vec3( 0,  1,  0), glm::vec2(tU, 0));
    vertices.emplace_back(glm::vec3(-0.5 * w,  0.5 * h, -0.5 * d), glm::vec3( 0,  1,  0), glm::vec2(0, tV));
    vertices.emplace_back(glm::vec3( 0.5 * w,  0.5 * h, -0.5 * d), glm::vec3( 0,  1,  0), glm::vec2(tU, tV));

    vertices.emplace_back(glm::vec3(-0.5 * w, -0.5 * h, -0.5 * d), glm::vec3( 0, -1,  0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3( 0.5 * w, -0.5 * h, -0.5 * d), glm::vec3( 0, -1,  0), glm::vec2(btU, 0));
    vertices.emplace_back(glm::vec3(-0.5 * w, -0.5 * h,  0.5 * d), glm::vec3( 0, -1,  0), glm::vec2(0, btV));
    vertices.emplace_back(glm::vec3( 0.5 * w, -0.5 * h,  0.5 * d), glm::vec3( 0, -1,  0), glm::vec2(btU, btV));

    vertices.emplace_back(glm::vec3( 0.5 * w, -0.5 * h,  0.5 * d), glm::vec3( 1,  0,  0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3( 0.5 * w, -0.5 * h, -0.5 * d), glm::vec3( 1,  0,  0), glm::vec2(rU, 0));
    vertices.emplace_back(glm::vec3( 0.5 * w,  0.5 * h,  0.5 * d), glm::vec3( 1,  0,  0), glm::vec2(0, rV));
    vertices.emplace_back(glm::vec3 (0.5 * w,  0.5 * h, -0.5 * d), glm::vec3( 1,  0,  0), glm::vec2(rU, rV));

    vertices.emplace_back(glm::vec3(-0.5 * w, -0.5 * h, -0.5 * d), glm::vec3(-1,  0,  0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(-0.5 * w, -0.5 * h,  0.5 * d), glm::vec3(-1,  0,  0), glm::vec2(lU, 0));
    vertices.emplace_back(glm::vec3(-0.5 * w,  0.5 * h, -0.5 * d), glm::vec3(-1,  0,  0), glm::vec2(0, lV));
    vertices.emplace_back(glm::vec3(-0.5 * w,  0.5 * h,  0.5 * d), glm::vec3(-1,  0,  0), glm::vec2(lU, lV));

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}

std::shared_ptr<Mesh> MeshFactory::createCube(GLfloat w, GLfloat h, GLfloat d) {
    return createCube(w, h, d, 1, 1, 1, 1);
}

std::shared_ptr<Mesh> MeshFactory::createCylinder(GLfloat r, GLfloat h, GLuint sides) {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
//                               {0, 2, 1,
//                                2, 3, 1,
//                                2, 4, 3,
//                                4, 5, 3,
//                                4, 6, 5,
//                                6, 7, 5,
//                                6, 8, 7,
//                                8, 9, 7,
//    };

    float deltaAngle = glm::two_pi<float>() / sides;

    for (GLuint i = 0; i <= sides; ++i) {
        float x = r * std::cos(deltaAngle * i);
        float y = r * std::sin(deltaAngle * i);

        vertices.emplace_back(glm::vec3(x, y, -h / 2), glm::normalize(glm::vec3(x, y, 0)), glm::vec2((float) i / sides, 0));
        vertices.emplace_back(glm::vec3(x, y, h / 2), glm::normalize(glm::vec3(x, y, 0)), glm::vec2((float) i / sides, 1));
    }

    for (GLuint i = 0; i < 2*sides - 1; ++i) {
        indices.emplace_back(2 * ((i + 1) / 2));
        indices.emplace_back(i + 2);
        indices.emplace_back(2 * ((i + 1) / 2) + 1);

        indices.emplace_back(2 * ((i + 2) / 2));
        indices.emplace_back(i + 3);
        indices.emplace_back(2 * ((i + 1) / 2) + 1);
    }

    // Caps
    GLuint centerIdx  = (GLuint) vertices.size();
    vertices.emplace_back(glm::vec3(0, 0, -h / 2), glm::vec3(0, 0, -1), glm::vec2(0.5, 0.5));
    for (GLuint i = 0; i <= sides; ++i) {
        float x = r * std::cos(deltaAngle * i);
        float y = r * std::sin(deltaAngle * i);

        vertices.emplace_back(glm::vec3(x, y, -h / 2), glm::vec3(0, 0, -1), glm::vec2((x/r + 1)/2, (y/r+1)/2));
    }

    for (GLuint i = 1; i < sides + 1; ++i) {
        indices.emplace_back(centerIdx);
        indices.emplace_back(centerIdx + i);
        indices.emplace_back(centerIdx + i + 1);
    }

    centerIdx  = (GLuint) vertices.size();
    vertices.emplace_back(glm::vec3(0, 0,  h / 2), glm::vec3(0, 0, 1), glm::vec2(0.5, 0.5));
    for (GLuint i = 0; i <= sides; ++i) {
        float x = r * std::cos(deltaAngle * i);
        float y = r * std::sin(deltaAngle * i);

        vertices.emplace_back(glm::vec3(x, y, h / 2), glm::vec3(0, 0, 1), glm::vec2((-x/r + 1)/2, (y/r+1)/2));
    }

    for (GLuint i = 1; i < sides + 1; ++i) {
        indices.emplace_back(centerIdx);
        indices.emplace_back(centerIdx + i);
        indices.emplace_back(centerIdx + i + 1);
    }


    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}


std::shared_ptr<Mesh> MeshFactory::loadFromFile(std::string fileName) {
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
        vertices.emplace_back(glm::vec3(data[0], data[1], data[2]), glm::vec3(), glm::vec2(data[3], data[4]));
    }

    for (GLuint i = 0; i < indicesCount; ++i) {
        float data;
        file >> data;
        indices.emplace_back(data);
    }

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}

std::shared_ptr<Mesh> MeshFactory::loadFromObjFile(std::string fileName) {
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
                    return vertex.position == vertices[v] && vertex.textCoord == textCoords[t] &&
                           vertex.normal == normals[n];
                });

                if (idx == resVertices.end()) {
                    resVertices.emplace_back(vertices[v], normals[n], textCoords[t]);
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

void MeshFactory::genearateCodeFrmObj(std::string fileName) {
    auto res = loadFromObjFile("resources/cube.obj");

    std::cout << "std::vector<Vertex> vertices;" << "\n";
    std::cout << "std::vector<GLuint> indices{ ";
    for (auto i : res->mIndices)
        std::cout << i << ",";
    std::cout << "};\n";

    for (auto v : res->mVertices)
        std::cout << "vertices.emplace_back(glm::vec3("
                  << v.position.x << "*w" << ", " << v.position.y << "*h" << ", " << v.position.z << "*d"
                  << "), glm::vec3("
                  << v.normal.x << ", " << v.normal.y << ", " << v.normal.z
                  << "), glm::vec2("
                  << v.textCoord.x << ", " << v.textCoord.y
                  << "));\n";

}
