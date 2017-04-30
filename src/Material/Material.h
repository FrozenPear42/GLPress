#ifndef GKOM_INTRO_MATERIAL_H
#define GKOM_INTRO_MATERIAL_H

#include <cstdlib>
#include <string>
#include <memory>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "Texture.h"

class Material {
    friend class Renderer;

private:
    std::shared_ptr<Texture> mDiffuseMap;
    std::shared_ptr<Texture> mNormalMap;
    std::shared_ptr<Texture> mSpecularMap;
    GLfloat mShiness;
public:

    Material(std::string directory, std::string name);
};

#endif //GKOM_INTRO_MATERIAL_H
