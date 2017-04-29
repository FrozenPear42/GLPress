#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "Model.h"

void Model::setTransform(glm::mat4 transform) {
    mTransform = transform;
}

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : mMesh(std::move(mesh)), mMaterial(std::move(material)) {}
