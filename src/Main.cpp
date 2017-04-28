#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils/Window.h"
#include "Main.h"


Main::Main() : mWindow(800, 600, "Kocham GKOM <3"), mCameraPosition(0.0f, 0.0f, 10.0f), mDelta(0.0f), mLastFrame(0.0f),
               mCameraHAngle(-glm::half_pi<GLfloat>()), mCameraVAngle(0), mCameraDistance(10) {

    mView = glm::lookAt(mCameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mProjection = glm::perspective(45.0f, (GLfloat) 800 / 600, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    mCube = std::make_shared<Model>(Mesh::loadFromObjFile("resources/cube.obj"),
                                    std::make_shared<Material>("resources/materials/", "metal"));
    mCube2 = std::make_shared<Model>(Mesh::loadFromObjFile("resources/cube.obj"),
                                     std::make_shared<Material>("resources/materials/", "metal"));


    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0, 0, -3));
    mCube->setTransform(trans);
    trans = glm::translate(trans, glm::vec3(0, 0, 3));
    mCube2->setTransform(trans);
}


bool Main::nextFrame() {
    GLfloat currentFrame = (GLfloat) glfwGetTime();
    mDelta = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    mWindow.poolEvents();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat cameraSpeed = mDelta;
    if (mWindow.isPressed(GLFW_KEY_UP))
        mCameraVAngle += cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_DOWN))
        mCameraVAngle += cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_RIGHT))
        mCameraHAngle += cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_LEFT))
        mCameraHAngle -= cameraSpeed;


    mCameraPosition.x = (float) (mCameraDistance * cos(mCameraHAngle));
    mCameraPosition.y = (float) (mCameraDistance * sin(mCameraVAngle));
    mCameraPosition.z = (float) (mCameraDistance * sin(mCameraHAngle));


    mView = glm::lookAt(mCameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    mCube->draw(mProjection, mView);
    mCube2->draw(mProjection, mView);

    mWindow.swapBuffers();
    return !mWindow.isFinalize();
}


int main() {
    Main scene;
    while (scene.nextFrame());
    return 0;
}