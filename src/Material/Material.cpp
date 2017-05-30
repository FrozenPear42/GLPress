#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include "Material.h"
#include "Texture.h"
#include "../Utils/GLSLProgramCompiler.h"

Material::Material(std::string directory, std::string name) {
    mDiffuseMap = Texture::loadFromFile(directory + name + "_diff.jpg");
    mNormalMap = Texture::loadFromFile(directory + name + "_normal.jpg");
}

