#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils/Window.h"
#include "Main.h"
#include "Model/MeshFactory.h"
#include "Light/DirectLight.h"
#include "Light/PointLight.h"


Main::Main() : mWindow(800, 600, "Kocham GKOM <3"), mDelta(0.0f), mLastFrame(0.0f),
               mCameraVAngle(glm::quarter_pi<GLfloat>()), mCameraHAngle(glm::quarter_pi<GLfloat>()),
               mCameraDistance(50) {

    mMainScene = std::make_shared<Scene>();
    mCamera = std::make_shared<Camera>(mCameraPosition, glm::vec3(0, 0, 0));

    auto metalMaterial = std::make_shared<Material>("resources/materials/", "metal");

    mBase = std::make_shared<Model>(MeshFactory::createCube(30, 2, 40), metalMaterial);
    mColumnLeft = std::make_shared<Model>(MeshFactory::createCube(3, 10, 3), metalMaterial);
    mColumnRight = std::make_shared<Model>(MeshFactory::createCube(3, 10, 3), metalMaterial);
    mColumnLeft->setPosition(glm::vec3(-10, 5, 0));
    mColumnRight->setPosition(glm::vec3(10, 5, 0));
    mHandler = std::make_shared<Model>(MeshFactory::createCube(23, 3, 3), metalMaterial);
    mHandler->setPosition(glm::vec3(0, 11.5f, 0));
    mPress = std::make_shared<Model>(MeshFactory::createCylinder(1, 13, 24), metalMaterial);
    mPress->setRotation(glm::vec3(-glm::half_pi<float>(), 0, 0));
    mPress->setPosition(glm::vec3(0, 10, 0));

    mTransportFront = std::make_shared<Model>(MeshFactory::createCylinder(0.5, 8, 24), metalMaterial);
    mTransportFront->setPosition(glm::vec3(0, 2, 15));
    mTransportFront->setRotation(glm::vec3(0, -glm::half_pi<float>(), 0));

    mTransportBack = std::make_shared<Model>(MeshFactory::createCylinder(0.5, 8, 24), metalMaterial);
    mTransportBack->setPosition(glm::vec3(0, 2, -15));
    mTransportBack->setRotation(glm::vec3(0, -glm::half_pi<float>(), 0));

    mTransportTop = std::make_shared<Model>(MeshFactory::createPlane(8, 30), metalMaterial);
    mTransportTop->setRotation(glm::vec3(-glm::half_pi<float>(), 0, 0));
    mTransportTop->setPosition(glm::vec3(0,2.5,0));

    mTransportBottom = std::make_shared<Model>(MeshFactory::createPlane(8, 30), metalMaterial);
    mTransportBottom->setRotation(glm::vec3(glm::half_pi<float>(), 0, 0));
    mTransportBottom->setPosition(glm::vec3(0,1.5,0));


    mMainScene->addModel(mBase);
    mMainScene->addModel(mColumnLeft);
    mMainScene->addModel(mColumnRight);
    mMainScene->addModel(mHandler);
    mMainScene->addModel(mPress);
    mMainScene->addModel(mTransportFront);
    mMainScene->addModel(mTransportBack);
    mMainScene->addModel(mTransportTop);
    mMainScene->addModel(mTransportBottom);

//    auto light = std::make_shared<DirectLight>(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.5, 0.7, 0.8), 1.0f);
    auto light = std::make_shared<PointLight>(glm::vec3(10, 12, 10), glm::vec3(0.5, 0.7, 0.8), 10.0f, 1.0f);
    mMainScene->addLight(light);
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