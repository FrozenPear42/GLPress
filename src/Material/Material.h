#ifndef GKOM_INTRO_MATERIAL_H
#define GKOM_INTRO_MATERIAL_H

#include <cstdlib>
#include <string>
#include <memory>
#include <GL/glew.h>
#include "Texture.h"

class Material {
private:
    GLuint mProgram;
    std::shared_ptr<Texture> mDiffuseMap;
    std::shared_ptr<Texture> mNormalMap;

public:
    Material(std::string directory, std::string name);

    void use();
};

#endif //GKOM_INTRO_MATERIAL_H
