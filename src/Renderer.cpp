#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Utils/GLSLProgramCompiler.h"

Renderer::Renderer() {

    glEnable(GL_DEPTH_TEST);

    mMainShaderProgram = GLSLProgramCompiler::fromFiles("resources/shaders/main.vert", "resources/shaders/main.frag");

    mModelUniform = glGetUniformLocation(mMainShaderProgram, "model");
    mViewUniform = glGetUniformLocation(mMainShaderProgram, "view");
    mProjectionUniform = glGetUniformLocation(mMainShaderProgram, "projection");

    mDiffuseMapUniform = glGetUniformLocation(mMainShaderProgram, "diffuseMap");
    mNormalMapUniform = glGetUniformLocation(mMainShaderProgram, "normalMap");
    mTimeUniform = glGetUniformLocation(mMainShaderProgram, "time");

}

void Renderer::renderScene(std::shared_ptr<Scene>& scene, std::shared_ptr<Camera>& camera) {

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mMainShaderProgram);

    glUniformMatrix4fv(mProjectionUniform, 1, GL_FALSE, glm::value_ptr(camera->mProjection));
    glUniformMatrix4fv(mViewUniform, 1, GL_FALSE, glm::value_ptr(camera->mView));

    auto light = std::make_shared<Light>();
    for (auto&& model : scene->mModels) {
        renderModel(model, light);
    }
}

void Renderer::renderModel(std::shared_ptr<Model>& model, std::shared_ptr<Light> light) {
    glUniformMatrix4fv(mModelUniform, 1, GL_FALSE, glm::value_ptr(model->mTransform));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->mMaterial->mDiffuseMap->getID());
    glUniform1i(mDiffuseMapUniform, GL_TEXTURE0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, model->mMaterial->mNormalMap->getID());
    glUniform1i(mNormalMapUniform, GL_TEXTURE1);

    model->mMesh->draw();
}

