#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils/Window.h"
#include "Main.h"
#include "Model/MeshFactory.h"
#include "Utils/Logger.h"
#include "Animation/AnimationModelMove.h"
#include "Animation/AnimationSequence.h"
#include "Light/DirectLight.h"
#include "Animation/AnimationDelay.h"
#include "Animation/AnimationMaterialOpacity.h"

Main::Main() : mWindow(800, 600, "Kocham GKOM <3"), mDelta(0.0f), mLastFrame(0.0f),
               mCameraDistance(50), mCameraVAngle(glm::quarter_pi<GLfloat>()),
               mCameraHAngle(glm::quarter_pi<GLfloat>()),
               mLightPosition(glm::vec3(0, 0, 0)) {

    mMainScene = std::make_shared<Scene>();
    mCamera = std::make_shared<Camera>(mCameraPosition, glm::vec3(0, 0, 0));

    mSkybox = std::make_shared<Skybox>("resources/skybox/", "skybox");
    mMainScene->setSkybox(mSkybox);

    auto metalMaterial = std::make_shared<Material>("resources/materials/", "rusty");

    mBase = std::make_shared<Model>(MeshFactory::createCube(30, 2, 40), metalMaterial);

    mColumnLeft = std::make_shared<Model>(MeshFactory::createCube(3, 10, 3), metalMaterial);
    mColumnLeft->setPosition(glm::vec3(-10, 5, 0));

    mColumnRight = std::make_shared<Model>(MeshFactory::createCube(3, 10, 3), metalMaterial);
    mColumnRight->setPosition(glm::vec3(10, 5, 0));

    mHandler = std::make_shared<Model>(MeshFactory::createCube(23, 3, 3), metalMaterial);
    mHandler->setPosition(glm::vec3(0, 11.5f, 0));

    mPress = std::make_shared<Model>(MeshFactory::createCylinder(1, 13, 24), metalMaterial);
    mPress->setRotation(glm::vec3(-glm::half_pi<float>(), 0, 0));
    mPress->setPosition(glm::vec3(0, 9, 0));

    mTransportFront = std::make_shared<Model>(MeshFactory::createCylinder(0.5, 8, 24), metalMaterial);
    mTransportFront->setPosition(glm::vec3(0, 2, 15));
    mTransportFront->setRotation(glm::vec3(0, -glm::half_pi<float>(), 0));

    mTransportBack = std::make_shared<Model>(MeshFactory::createCylinder(0.5, 8, 24), metalMaterial);
    mTransportBack->setPosition(glm::vec3(0, 2, -15));
    mTransportBack->setRotation(glm::vec3(0, -glm::half_pi<float>(), 0));

    mTransportTop = std::make_shared<Model>(MeshFactory::createPlane(8, 30), metalMaterial);
    mTransportTop->setRotation(glm::vec3(-glm::half_pi<float>(), 0, 0));
    mTransportTop->setPosition(glm::vec3(0, 2.5, 0));

    mTransportBottom = std::make_shared<Model>(MeshFactory::createPlane(8, 30), metalMaterial);
    mTransportBottom->setRotation(glm::vec3(glm::half_pi<float>(), 0, 0));
    mTransportBottom->setPosition(glm::vec3(0, 1.5, 0));

    for (int i = 0; i < 1; ++i) {
        auto coin = std::make_shared<Model>(MeshFactory::createCylinder(1, 0.5, 24), metalMaterial);
        coin->setRotation(glm::vec3(-glm::half_pi<float>(), 0, 0));
        coin->setPosition(glm::vec3(0, 3, 8 * (i - 1.5)));
        mCoins.emplace_back(coin);
    }

    mMainScene->addModel(mBase);
    mMainScene->addModel(mColumnLeft);
    mMainScene->addModel(mColumnRight);
    mMainScene->addModel(mHandler);
    mMainScene->addModel(mPress);
    mMainScene->addModel(mTransportFront);
    mMainScene->addModel(mTransportBack);
    mMainScene->addModel(mTransportTop);

    for (auto&& coin : mCoins)
        mMainScene->addModel(coin);

//     mMainScene->addModel(std::make_shared<Model>(MeshFactory::createCylinder(10, 10, 20), metalMaterial));

    auto light = std::make_shared<DirectLight>(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.5, 0.7, 0.8), 4.0f);
//    mSpotLight = std::make_shared<PointLight>(glm::vec3(10, 12, 10), glm::vec3(0.5, 0.7, 0.8), 10.0f, 1.0f);
    mSpotLight = std::make_shared<SpotLight>(glm::vec3(0, 15, 0), glm::vec3(0, -1, 0), glm::vec3(0.5, 0.7, 0.8),
                                             glm::radians(12.5f), 10.0f, 1.0f);
    mMainScene->addLight(light);


    auto seq = std::make_unique<AnimationSequence>();
    seq->addToSequence(std::make_unique<AnimationModelMove>(mPress, glm::vec3(0, 2, 0), 2));
    seq->addToSequence(std::make_unique<AnimationModelMove>(mPress, -glm::vec3(0, 2, 0), 0.5));
    seq->setLooped(true);

    mCoins[0]->setPosition(glm::vec3(0, 6, -12));
    auto coinAnimation = std::make_unique<AnimationSequence>();
    coinAnimation->addToSequence(std::make_unique<AnimationModelMove>(mCoins[0], glm::vec3(0, -3, 0), 1));
    coinAnimation->addToSequence(std::make_unique<AnimationModelMove>(mCoins[0], glm::vec3(0, 0, 12), 3));
    coinAnimation->addToSequence(std::make_unique<AnimationDelay>(3));
    coinAnimation->addToSequence(std::make_unique<AnimationModelMove>(mCoins[0], glm::vec3(0, 0, 12), 3));

    mAnimations.emplace_back(std::move(seq));
    mAnimations.emplace_back(std::move(coinAnimation));

    for (auto&& anim : mAnimations)
        anim->animationStart();
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

    if (mWindow.isPressed(GLFW_KEY_S))
        mLightPosition.z += 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_W))
        mLightPosition.z -= 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_D))
        mLightPosition.x += 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_A))
        mLightPosition.x -= 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_PAGE_UP))
        mLightPosition.y += 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_PAGE_DOWN))
        mLightPosition.y -= 10 * cameraSpeed;


    mCameraPosition.x = (float) (mCameraDistance * cos(mCameraHAngle));
    mCameraPosition.y = (float) (mCameraDistance * sin(mCameraVAngle));
    mCameraPosition.z = (float) (mCameraDistance * sin(mCameraHAngle));

    for (auto&& anim : mAnimations)
        anim->animationStep(mDelta);

    mCamera->setPosition(mCameraPosition);
    mSpotLight->setTarget(mLightPosition);
    mRenderer.renderScene(mMainScene, mCamera);

    mWindow.swapBuffers();
    return !mWindow.isFinalize();
}


int main() {
    Main scene;
    while (scene.nextFrame());
    return 0;
}