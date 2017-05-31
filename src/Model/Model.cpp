#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : mMesh(std::move(mesh)),
                                                                               mMaterial(std::move(material)) {}


void Model::setTransform(glm::mat4 transform) {
    mTransform = transform;
}

void Model::recalculateTransform() {
    glm::mat4 unit;
    auto translate = glm::translate(unit, mPosition);
    auto rotate = glm::rotate(translate, mRotation.x, glm::vec3(1, 0, 0));
    rotate = glm::rotate(rotate, mRotation.y, glm::vec3(0, 1, 0));
    mTransform = glm::rotate(rotate, mRotation.z, glm::vec3(0, 0, 1));
}

void Model::setPosition(glm::vec3 position) {
    if (mPosition == position)
        return;
    mPosition = position;
    recalculateTransform();
}

void Model::setRotation(glm::vec3 rotation) {
    if (mRotation == rotation)
        return;
    mRotation = rotation;
    recalculateTransform();
}

