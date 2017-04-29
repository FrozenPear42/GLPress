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
    GLint mTimeUniform;

private:
    void renderModel(std::shared_ptr<Model>& model, std::shared_ptr<Light> light);

public:
    Renderer();

    void renderScene(std::shared_ptr<Scene>& scene, std::shared_ptr<Camera>& camera);
};


#endif //GLPRESS_RENDERER_H
