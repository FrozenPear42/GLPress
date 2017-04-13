#ifndef GLPRESS_MESH_H
#define GLPRESS_MESH_H

#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <GL/gl.h>
#include <memory>

struct Vertex {
    glm::vec3 position;
    glm::vec2 textCoord;
    Vertex() {};
    Vertex(glm::vec3 position, glm::vec2 textCoord) : position(position), textCoord(textCoord) {}
};

class Mesh {

public:
    static std::shared_ptr<Mesh> loadFromFile(std::string fileName);
    Mesh(std::vector<Vertex>&& vertices, std::vector<GLuint>&& indices);
    void draw();

private:
    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndices;

    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;

};


#endif //GLPRESS_MESH_H
