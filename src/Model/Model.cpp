#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "Model.h"

void Model::draw(glm::mat4 projection, glm::mat4 view) {
    mMaterial->use(projection, view, mTransform);
    mMesh->draw();
}

void Model::setTransform(glm::mat4 transform) {
    mTransform = transform;
}

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : mMesh(std::move(mesh)), mMaterial(std::move(material)) {}
