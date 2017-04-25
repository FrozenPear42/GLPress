#include <glm/gtc/type_ptr.hpp>
#include "Material.h"
#include "Texture.h"
#include "../Utils/GLSLProgramCompiler.h"

Material::Material(std::string directory, std::string name) {
    mDiffuseMap = Texture::loadFromFile(directory + name + "_diff.png");
    mNormalMap = Texture::loadFromFile(directory + name + "_normal.png");
    mProgram = GLSLProgramCompiler::fromFiles(directory + name + ".vert", directory + name + ".frag");

    mModelUniform = glGetUniformLocation(mProgram, "model");
    mViewUniform = glGetUniformLocation(mProgram, "view");
    mProjectionUniform = glGetUniformLocation(mProgram, "projection");

    mDiffuseMapUniform = glGetUniformLocation(mProgram, "diffuseMap");
    mNormalMapUniform = glGetUniformLocation(mProgram, "normalMap");
    mTimeUniform = glGetUniformLocation(mProgram, "time");
}

void Material::use(glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
    glUseProgram(mProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mDiffuseMap->getID());
    glUniform1i(mDiffuseMapUniform, GL_TEXTURE0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mNormalMap->getID());
    glUniform1i(mNormalMapUniform, GL_TEXTURE1);

    glUniformMatrix4fv(mProjectionUniform, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(mViewUniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(mModelUniform, 1, GL_FALSE, glm::value_ptr(model));

}
