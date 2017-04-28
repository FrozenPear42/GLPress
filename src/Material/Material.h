#ifndef GKOM_INTRO_MATERIAL_H
#define GKOM_INTRO_MATERIAL_H

#include <cstdlib>
#include <string>
#include <memory>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "Texture.h"

class Material {
private:
    GLuint mProgram;

    GLint mProjectionUniform;
    GLint mViewUniform;
    GLint mModelUniform;
    GLint mDiffuseMapUniform;
    GLint mNormalMapUniform;
    GLint mTimeUniform;

    std::shared_ptr<Texture> mDiffuseMap;
    std::shared_ptr<Texture> mNormalMap;
public:
    Material(std::string directory, std::string name);

    void use(glm::mat4 projection, glm::mat4 view, glm::mat4 model);

};

#endif //GKOM_INTRO_MATERIAL_H
