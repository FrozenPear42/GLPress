//
// Created by wojciech on 28.04.17.
//

#include "Scene.h"

void Scene::addModel(std::shared_ptr<Model> model) {
    mModels.push_back(model);
}

void Scene::removeModel(std::shared_ptr<Model> model) {
    mModels.remove(model);
}

void Scene::addLight(std::shared_ptr<Light> light) {
    mLights.push_back(light);
}

void Scene::removeLight(std::shared_ptr<Light> light) {
    mLights.remove(light);
}


void Scene::setSkybox(std::shared_ptr<Skybox> skybox) {
    mSkybox = skybox;
}

Scene::Scene() {}
