#include "Renderer.h"
#include "Utils/GLSLProgramCompiler.h"

Renderer::Renderer() {

    mMainShaderProgram = GLSLProgramCompiler::fromFiles("resources/shaders/main.vert", "resources/shaders/main.frag");

    mModelUniform = glGetUniformLocation(mMainShaderProgram, "model");
    mViewUniform = glGetUniformLocation(mMainShaderProgram, "view");
    mProjectionUniform = glGetUniformLocation(mMainShaderProgram, "projection");

    mDiffuseMapUniform = glGetUniformLocation(mMainShaderProgram, "diffuseMap");
    mNormalMapUniform = glGetUniformLocation(mMainShaderProgram, "normalMap");
    mTimeUniform = glGetUniformLocation(mMainShaderProgram, "time");

}

void Renderer::renderScene(std::shared_ptr<Scene>& scene) {
    auto light = std::make_shared<Light>();
    for (auto&& model : scene->mModels) {
        renderModel(model, light);
    }
}

void Renderer::renderModel(std::shared_ptr<Model>& model, std::shared_ptr<Light> light) {

}

