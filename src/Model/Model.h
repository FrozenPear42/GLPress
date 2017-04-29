#ifndef GLPRESS_MODEL_H
#define GLPRESS_MODEL_H

#include "Mesh.h"
#include "../Material/Texture.h"
#include "../Material/Material.h"

class Model {
    friend class Renderer;

public:
    void setTransform(glm::mat4 transform);

    Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    void setPosition(glm::vec3 position);

    void setRotation(glm::vec3 rotation);

private:
    void recalculateTransform();

private:
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Material> mMaterial;
    glm::mat4 mTransform;

    glm::vec3 mPosition;
    glm::vec3 mRotation;
};


#endif //GLPRESS_MODEL_H
