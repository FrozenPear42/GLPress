#pragma once

#include <vector>

class CubeModel {
    GLuint VAO;
    GLuint VBO;
    std::vector<GLfloat> cube_coord;

public:
    CubeModel(GLfloat size);

    ~CubeModel();

    void Draw(const glm::mat4&, GLint modelLoc) const;
};

