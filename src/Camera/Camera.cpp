#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 target) : mTarget(target) {
    mView = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
    mProjection = glm::perspective(45.0f, (GLfloat) 800 / 600, 0.1f, 100.0f);
}

void Camera::setPosition(glm::vec3 position) {
    mView = glm::lookAt(position, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}
