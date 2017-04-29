#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils/Window.h"
#include "Main.h"
#include "Model/MeshFactory.h"


Main::Main() : mWindow(800, 600, "Kocham GKOM <3"), mCameraPosition(0.0f, 0.0f, 10.0f), mDelta(0.0f), mLastFrame(0.0f),
               mCameraVAngle(0), mCameraHAngle(-glm::half_pi<GLfloat>()), mCameraDistance(10) {

    mMainScene = std::make_shared<Scene>();
    mCamera = std::make_shared<Camera>(mCameraPosition, glm::vec3(0, 0, 0));

    auto metalMaterial = std::make_shared<Material>("resources/materials/", "metal");

    mCube = std::make_shared<Model>(MeshFactory::createCube(2, 2, 2), metalMaterial);
    mCube2 = std::make_shared<Model>(MeshFactory::createCube(1, 1, 1), metalMaterial);

    auto cylinder = std::make_shared<Model>(MeshFactory::createCylinder(1, 1, 24), metalMaterial);

    mMainScene->addModel(mCube);
    mMainScene->addModel(mCube2);
    mMainScene->addModel(cylinder);

    auto light = std::make_shared<Light>();
    mMainScene->addLight(light);

    mCube->setPosition(glm::vec3(0, 0, -3));
    mCube2->setPosition(glm::vec3(0, 0, 3));
    mCube->setRotation(glm::vec3(glm::quarter_pi<float>(), 0, 0));

}


bool Main::nextFrame() {
    GLfloat currentFrame = (GLfloat) glfwGetTime();
    mDelta = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    mWindow.poolEvents();

    GLfloat cameraSpeed = mDelta;
    if (mWindow.isPressed(GLFW_KEY_UP))
        mCameraVAngle += cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_DOWN))
        mCameraVAngle -= cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_RIGHT))
        mCameraHAngle += cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_LEFT))
        mCameraHAngle -= cameraSpeed;

    mCameraPosition.x = (float) (mCameraDistance * cos(mCameraHAngle));
    mCameraPosition.y = (float) (mCameraDistance * sin(mCameraVAngle));
    mCameraPosition.z = (float) (mCameraDistance * sin(mCameraHAngle));

    mCamera->setPosition(mCameraPosition);
    mRenderer.renderScene(mMainScene, mCamera);

    mWindow.swapBuffers();
    return !mWindow.isFinalize();
}


int main() {
    Main scene;
    while (scene.nextFrame());
    return 0;
}