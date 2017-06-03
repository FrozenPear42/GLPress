#ifndef GLPRESS_RENDERER_H
#define GLPRESS_RENDERER_H


#include "Scene/Scene.h"

class Renderer {
private:
    GLuint mMainShaderProgram;

    GLint mProjectionUniform;
    GLint mViewUniform;
    GLint mModelUniform;

    GLint mDiffuseMapUniform;
    GLint mNormalMapUniform;
    GLint mSpecularMapUniform;

    GLint mOpacityUniform;
    GLint mTextureDisplacementUniform;

    GLint mLightTypeUniform;
    GLuint mDirectLightType;
    GLuint mPointLightType;
    GLuint mSpotLightType;

    GLint mPositionLightUniform;
    GLint mDirectionLightUniform;

    GLint mDiffuseLightUniform;
    GLint mSpecularLightUniform;

    GLint mCutOffLightUniform;
    GLint mOuterCutOffLightUniform;

    GLint mConstantLightUniform;
    GLint mLinearLightUniform;
    GLint mQuadraticLightUniform;


    GLuint mSkyboxShaderProgram;
    GLint mSkyboxTextureUniform;
    GLint mSkyboxProjectionUniform;
    GLint mSkyboxViewUniform;

    GLuint mAmbientShader;
    GLint mAmbientDiffuseUniform;
    GLint mAmbientProjectionUniform;
    GLint mAmbientViewUniform;
    GLint mAmbientModelUniform;
    GLint mAmbientTextureDisplacementUniform;
    GLint mAmbientAmbient;

    glm::vec4 mAmbientColor;

private:
    void renderModel(std::shared_ptr<Model>& model);

public:
    Renderer();

    void renderScene(std::shared_ptr<Scene>& scene, std::shared_ptr<Camera>& camera);

};


#endif //GLPRESS_RENDERER_H
