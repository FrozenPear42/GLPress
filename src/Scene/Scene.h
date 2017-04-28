#ifndef GLPRESS_SCENE_H
#define GLPRESS_SCENE_H

#include <list>
#include <GL/glew.h>
#include "../Model/Model.h"
#include "../Light/Light.h"
#include "../Camera/Camera.h"

class Scene {
private:
    std::list<Model> mModels;
    std::list<Light> mLights;
    GLuint mShadingProgram;
public:
    Scene();

    void addModel(std::shared_ptr<Model> model);

    void removeModel(std::shared_ptr<Model> model);

    void renderCamera(std::shared_ptr<Camera> camera);
};


#endif //GLPRESS_SCENE_H
