#ifndef GLPRESS_MODEL_H
#define GLPRESS_MODEL_H

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Mesh.h"
#include "../Material/Texture.h"
#include "../Material/Material.h"

class Model {
public:
    void setTransform(glm::mat4 transform);

    void draw(glm::mat4 projection, glm::mat4 view);

    Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

private:
    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Material> mMaterial;
    glm::mat4 mTransform;
};


#endif //GLPRESS_MODEL_H
