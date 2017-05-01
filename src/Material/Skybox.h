#ifndef GLPRESS_SKYBOX_H
#define GLPRESS_SKYBOX_H

#include <string>
#include <GL/glew.h>
#include <vector>

class Skybox {
    friend class Renderer;
public:
    Skybox(std::string directory, std::string name);

    void draw();

private:
    GLuint mTexture;
    GLuint mVAO;
    GLuint mVBO;
    std::vector<GLfloat> mVertices;
};

#endif //GLPRESS_SKYBOX_H
