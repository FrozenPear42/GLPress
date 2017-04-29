#ifndef GLPRESS_SCENE_H
#define GLPRESS_SCENE_H

#include <list>
#include <GL/glew.h>
#include "../Model/Model.h"
#include "../Light/Light.h"
#include "../Camera/Camera.h"

class Scene {
    friend class Renderer;
private:
    std::list<std::shared_ptr<Model>> mModels;
    std::list<std::shared_ptr<Light>> mLights;


public:
    Scene();

    void addModel(std::shared_ptr<Model> model);

    void removeModel(std::shared_ptr<Model> model);

    void addLight(std::shared_ptr<Light> light);

    void removeLight(std::shared_ptr<Light> light);

};


#endif //GLPRESS_SCENE_H
