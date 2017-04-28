#ifndef GLPRESS_CAMERA_H
#define GLPRESS_CAMERA_H


#include <glm/detail/type_mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera {
    friend class Scene;
private:
    glm::mat4 mProjection;
    glm::mat4 mView;
    glm::vec3 mPostion;
public:
    Camera(glm::vec3 position, glm::vec3 target);
    void setPosition(glm::vec3 position);
};


#endif //GLPRESS_CAMERA_H
