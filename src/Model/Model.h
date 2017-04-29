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

private:
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Material> mMaterial;
    glm::mat4 mTransform;
};


#endif //GLPRESS_MODEL_H
