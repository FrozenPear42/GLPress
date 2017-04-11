#ifndef GLPRESS_MESH_H
#define GLPRESS_MESH_H

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <GL/gl.h>

class Mesh {
public:
    typedef struct {
        glm::vec3 position;
        glm::vec2 textCoord;
    } Vertex;
private:
    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndices;

    GLuint mVBO;
    GLuint mEBO;
    GLuint mVBA;

public:
    static Mesh* fromFile(std::string fileName);
    Mesh();
};


#endif //GLPRESS_MESH_H
