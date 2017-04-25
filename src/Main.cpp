#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils/GLSLProgramCompiler.h"
#include "Utils/Window.h"
#include "Main.h"

GLfloat pitch = 0.0f;
const GLfloat pitch_max = 80.0f;
const GLfloat pitch_min = -80.0f;

GLfloat yaw = 0.0f;
const GLfloat yaw_max = 360.0f;
const GLfloat yaw_min = 0.0f;


Main::Main() : mWindow(800, 600, "Kocham GKOM <3"), mCameraPosition(0.0f, 0.0f, 3.0f), mDelta(0.0f), mLastFrame(0.0f) {

    mView = glm::lookAt(mCameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mProjection = glm::perspective(45.0f, (GLfloat) 800 / 600, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    mCube = std::make_shared<Model>(Mesh::loadFromObjFile("resources/cube.obj"), std::make_shared<Material>("resources/materials/", "metal"));
}


bool Main::nextFrame() {
    GLfloat currentFrame = (GLfloat) glfwGetTime();
    mDelta = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    mWindow.poolEvents();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat cameraSpeed = 100.0f * mDelta;
    if (mWindow.isPressed(GLFW_KEY_UP))
        if ((pitch += cameraSpeed) > pitch_max)
            pitch = pitch_max;
    if (mWindow.isPressed(GLFW_KEY_DOWN))
        if ((pitch -= cameraSpeed) < pitch_min)
            pitch = pitch_min;
    if (mWindow.isPressed(GLFW_KEY_RIGHT))
        if ((yaw -= cameraSpeed) < yaw_min)
            yaw += yaw_max;
    if (mWindow.isPressed(GLFW_KEY_LEFT))
        if ((yaw += cameraSpeed) > yaw_max)
            yaw -= yaw_max;

    glm::mat4 trans;
    trans = glm::rotate(trans, glm::radians(pitch), glm::vec3(1, 0, 0));
    trans = glm::rotate(trans, glm::radians(yaw), glm::vec3(0, 1, 0));
    mCube->setTransform(trans);
    mCube->draw(mProjection, mView);

    mWindow.swapBuffers();
    return !mWindow.isFinalize();
}


int main() {
    Main scene;
    while (scene.nextFrame());
    return 0;
}