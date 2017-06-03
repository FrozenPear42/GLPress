#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include "Renderer.h"
#include "Utils/GLSLProgramCompiler.h"

Renderer::Renderer() : mAmbientColor(0.2, 0.2, 0.2, 1.0) {

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

    mMainShaderProgram = GLSLProgramCompiler::fromFiles("resources/shaders/main.vert", "resources/shaders/main.frag");

    mModelUniform = glGetUniformLocation(mMainShaderProgram, "model");
    mViewUniform = glGetUniformLocation(mMainShaderProgram, "view");
    mProjectionUniform = glGetUniformLocation(mMainShaderProgram, "projection");

    mDiffuseMapUniform = glGetUniformLocation(mMainShaderProgram, "diffuseMap");
    mNormalMapUniform = glGetUniformLocation(mMainShaderProgram, "normalMap");
    mSpecularMapUniform = glGetUniformLocation(mMainShaderProgram, "specularMap");

    mOpacityUniform = glGetUniformLocation(mMainShaderProgram, "opacity");
    mTextureDisplacementUniform = glGetUniformLocation(mMainShaderProgram, "textureDisplacement");

    mLightTypeUniform = glGetSubroutineUniformLocation(mMainShaderProgram, GL_FRAGMENT_SHADER, "lightType");
    mDirectLightType = glGetSubroutineIndex(mMainShaderProgram, GL_FRAGMENT_SHADER, "directLight");
    mPointLightType = glGetSubroutineIndex(mMainShaderProgram, GL_FRAGMENT_SHADER, "pointLight");
    mSpotLightType = glGetSubroutineIndex(mMainShaderProgram, GL_FRAGMENT_SHADER, "spotLight");

    mPositionLightUniform = glGetUniformLocation(mMainShaderProgram, "light.position");
    mDirectionLightUniform = glGetUniformLocation(mMainShaderProgram, "light.direction");
    mDiffuseLightUniform = glGetUniformLocation(mMainShaderProgram, "light.diffuse");
    mSpecularLightUniform = glGetUniformLocation(mMainShaderProgram, "light.specular");
    mCutOffLightUniform = glGetUniformLocation(mMainShaderProgram, "light.cutOff");
    mOuterCutOffLightUniform = glGetUniformLocation(mMainShaderProgram, "light.outerCutOff");
    mConstantLightUniform = glGetUniformLocation(mMainShaderProgram, "light.constant");
    mLinearLightUniform = glGetUniformLocation(mMainShaderProgram, "light.linear");
    mQuadraticLightUniform = glGetUniformLocation(mMainShaderProgram, "light.quadratic");

    mSkyboxShaderProgram = GLSLProgramCompiler::fromFiles("resources/shaders/skybox.vert",
                                                          "resources/shaders/skybox.frag");
    mSkyboxViewUniform = glGetUniformLocation(mSkyboxShaderProgram, "view");
    mSkyboxProjectionUniform = glGetUniformLocation(mSkyboxShaderProgram, "projection");
    mSkyboxTextureUniform = glGetUniformLocation(mSkyboxShaderProgram, "skybox");

    mAmbientShader = GLSLProgramCompiler::fromFiles("resources/shaders/ambient.vert", "resources/shaders/ambient.frag");

    mAmbientModelUniform = glGetUniformLocation(mAmbientShader, "model");
    mAmbientViewUniform = glGetUniformLocation(mAmbientShader, "view");
    mAmbientProjectionUniform = glGetUniformLocation(mAmbientShader, "projection");
    mAmbientDiffuseUniform = glGetUniformLocation(mAmbientShader, "diffuse");
    mAmbientAmbient = glGetUniformLocation(mAmbientShader, "ambient");
    mAmbientTextureDisplacementUniform = glGetUniformLocation(mAmbientShader, "textureDisplacement");

}

void Renderer::renderScene(std::shared_ptr<Scene>& scene, std::shared_ptr<Camera>& camera) {

    glDepthMask(GL_TRUE);

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Skybox
    if (scene->mSkybox) {
        glm::mat4 skyboxView(glm::mat3(camera->mView));

        glDepthMask(GL_FALSE);
        glUseProgram(mSkyboxShaderProgram);
        glUniformMatrix4fv(mSkyboxProjectionUniform, 1, GL_FALSE, glm::value_ptr(camera->mProjection));
        glUniformMatrix4fv(mSkyboxViewUniform, 1, GL_FALSE, glm::value_ptr(skyboxView));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, scene->mSkybox->mTexture);
        glUniform1i(mSkyboxTextureUniform, GL_TEXTURE0);

        scene->mSkybox->draw();
        glDepthMask(GL_TRUE);
    }

    //Ambient
    glUseProgram(mAmbientShader);
    glProgramUniformMatrix4fv(mAmbientShader, mAmbientProjectionUniform, 1, GL_FALSE, glm::value_ptr(camera->mProjection));
    glProgramUniformMatrix4fv(mAmbientShader, mAmbientViewUniform, 1, GL_FALSE, glm::value_ptr(camera->mView));
    glProgramUniform4fv(mAmbientShader, mAmbientAmbient, 1, glm::value_ptr(mAmbientColor));

    glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);

    for(auto&& model : scene->mModels)
    {
        glProgramUniformMatrix4fv(mAmbientShader, mAmbientModelUniform, 1, GL_FALSE, glm::value_ptr(model->mTransform));
        glProgramUniform2fv(mAmbientShader, mAmbientTextureDisplacementUniform, 1, glm::value_ptr(model->mMaterial->mTextureDisplacement));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model->mMaterial->mDiffuseMap->getID());
        glUniform1i(mAmbientDiffuseUniform, GL_TEXTURE0);
        model->mMesh->draw();
    }

    glDepthMask(GL_FALSE);

//    glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ONE);

    glUseProgram(mMainShaderProgram);

    glUniformMatrix4fv(mProjectionUniform, 1, GL_FALSE, glm::value_ptr(camera->mProjection));
    glUniformMatrix4fv(mViewUniform, 1, GL_FALSE, glm::value_ptr(camera->mView));

    for (auto&& light : scene->mLights) {

        if (light->getType() == Light::Type::POINT) {
            glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &mPointLightType);

            glUniform3fv(mPositionLightUniform, 1, glm::value_ptr(light->mPosition));
            glUniform3fv(mDiffuseLightUniform, 1, glm::value_ptr(light->mDiffuse));
            glUniform1f(mConstantLightUniform, light->mConstant);
            glUniform1f(mLinearLightUniform, light->mLinear);
            glUniform1f(mQuadraticLightUniform, light->mQuadratic);

        } else if (light->getType() == Light::Type::DIRECT) {
            glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &mDirectLightType);

            glUniform3fv(mDirectionLightUniform, 1, glm::value_ptr(light->mDirection));
            glUniform3fv(mDiffuseLightUniform, 1, glm::value_ptr(light->mDiffuse));

        } else if (light->getType() == Light::Type::SPOT) {
            glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &mSpotLightType);

            glUniform3fv(mPositionLightUniform, 1, glm::value_ptr(light->mPosition));
            glUniform3fv(mDirectionLightUniform, 1, glm::value_ptr(light->mDirection));
            glUniform3fv(mDiffuseLightUniform, 1, glm::value_ptr(light->mDiffuse));
            glUniform1f(mConstantLightUniform, light->mConstant);
            glUniform1f(mLinearLightUniform, light->mLinear);
            glUniform1f(mQuadraticLightUniform, light->mQuadratic);

            glUniform1f(mCutOffLightUniform, light->mCutOff);
            glUniform1f(mOuterCutOffLightUniform, light->mOuterCutOff);
        }

        for (auto&& model : scene->mModels) {
            renderModel(model);
        }
    }
}

void Renderer::renderModel(std::shared_ptr<Model>& model) {

    glUniformMatrix4fv(mModelUniform, 1, GL_FALSE, glm::value_ptr(model->mTransform));

    glUniform1f(mOpacityUniform, model->mMaterial->mOpacity);
    glUniform2fv(mTextureDisplacementUniform, 1, glm::value_ptr(model->mMaterial->mTextureDisplacement));

    glActiveTexture(GL_TEXTURE0);
    if (model->mMaterial->mMapping)
        glBindTexture(GL_TEXTURE_2D, model->mMaterial->mDiffuseMap->getID());
    else
        glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(mDiffuseMapUniform, GL_TEXTURE0);

//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, model->mMaterial->mNormalMap->getID());
//    glUniform1i(mNormalMapUniform, GL_TEXTURE1);

//    glActiveTexture(GL_TEXTURE2);
//    glBindTexture(GL_TEXTURE_2D, model->mMaterial->mSpecularMap->getID());
//    glUniform1i(mSpecularMapUniform, GL_TEXTURE2);

    model->mMesh->draw();

}

