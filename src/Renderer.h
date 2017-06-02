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
    GLint mTimeUniform;
    GLint mOpacityUniform;
    GLint mTextureDisplacementUniform;

    GLint mLightTypeUniform;
    GLuint mDirectLightType;
    GLuint mPointLightType;
    GLuint mSpotLightType;

    GLint mPositionLightUniform;
    GLint mDirectionLightUniform;

    GLint mAmbientLightUniform;
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


private:
    void renderModel(std::shared_ptr<Model>& model);

public:
    Renderer();

    void renderScene(std::shared_ptr<Scene>& scene, std::shared_ptr<Camera>& camera);

};


#endif //GLPRESS_RENDERER_H
