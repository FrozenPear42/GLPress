#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils/Window.h"
#include "Main.h"
#include "Model/OBJParser.h"
#include "Utils/Logger.h"
#include "Animation/AnimationModelMove.h"
#include "Animation/AnimationSequence.h"
#include "Light/DirectLight.h"
#include "Animation/AnimationDelay.h"
#include "Model/CylinderBuilder.h"
#include "Model/CubeBuilder.h"
#include "Model/PlaneBuilder.h"
#include "Animation/AnimationModelMaterialSwap.h"
#include "Animation/AnimationMaterialOpacity.h"
#include "Animation/AnimationConcurrent.h"
#include "Animation/AnimationTextureDisplacement.h"

Main::Main() : mWindow(800, 600, "Kocham GKOM <3"),
               mDelta(0.0f),
               mLastFrame(0.0f),
               mCameraDistance(50),
               mCameraVAngle(glm::quarter_pi<GLfloat>()),
               mCameraHAngle(glm::quarter_pi<GLfloat>()),
               mLightPosition(glm::vec3(0, 0, 0)) {

    mMainScene = std::make_shared<Scene>();
    mCamera = std::make_shared<Camera>(mCameraPosition, glm::vec3(0, 0, 0));

    mSkybox = std::make_shared<Skybox>("resources/skybox/", "skybox");
    mMainScene->setSkybox(mSkybox);

    auto brushedMaterial = std::make_shared<Material>(Texture::loadFromFile("resources/materials/brushed.jpg"));
    auto metalMaterial = std::make_shared<Material>(Texture::loadFromFile("resources/materials/green_metal.jpg"));
    auto conveyorMaterial = std::make_shared<Material>(Texture::loadFromFile("resources/materials/conveyor.png"));
    auto concreteMaterial = std::make_shared<Material>(Texture::loadFromFile("resources/materials/concrete.jpg"));

    auto coinBlankMaterial = std::make_shared<Material>(Texture::loadFromFile("resources/materials/coin_blank.jpg"));
    auto coinPressedMaterial = std::make_shared<Material>(Texture::loadFromFile("resources/materials/coin.jpg"));


    auto halfPI = glm::half_pi<float>();

    mBase = std::make_shared<Model>(CubeBuilder()
                                            .width(40)
                                            .height(2)
                                            .depth(40)
                                            .topMap(glm::vec2(0, 0), glm::vec2(8, 10))
                                            .bottomMap(glm::vec2(0, 0), glm::vec2(5, 10))
                                            .leftMap(glm::vec2(0, 0), glm::vec2(10, 1))
                                            .rightMap(glm::vec2(0, 0), glm::vec2(10, 1))
                                            .frontMap(glm::vec2(0, 0), glm::vec2(8, 1))
                                            .backMap(glm::vec2(0, 0), glm::vec2(8, 1))
                                            .build(),
                                    concreteMaterial);

    mColumnLeft = std::make_shared<Model>(CubeBuilder()
                                                  .width(3)
                                                  .height(12)
                                                  .depth(5)
                                                  .frontMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                  .leftMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                  .rightMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                  .backMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                  .topMap(glm::vec2(0, 0), glm::vec2(1, 1))
                                                  .bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
                                                  .build(),
                                          metalMaterial);
    mColumnLeft->setPosition(glm::vec3(-10, 6.5, 0));

    mColumnRight = std::make_shared<Model>(CubeBuilder()
                                                   .width(3)
                                                   .height(12)
                                                   .depth(5)
                                                   .frontMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                   .leftMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                   .rightMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                   .backMap(glm::vec2(0, 0), glm::vec2(1, 4))
                                                   .topMap(glm::vec2(0, 0), glm::vec2(1, 1))
                                                   .bottomMap(glm::vec2(0, 0), glm::vec2(1, 1))
                                                   .build(),
                                           metalMaterial);
    mColumnRight->setPosition(glm::vec3(10, 6.5, 0));

    mHandler = std::make_shared<Model>(CubeBuilder()
                                               .width(23)
                                               .height(3)
                                               .depth(5)
                                               .frontMap(glm::vec2(0, 0), glm::vec2(10, 1))
                                               .topMap(glm::vec2(0, 0), glm::vec2(10, 1))
                                               .backMap(glm::vec2(0, 0), glm::vec2(10, 1))
                                               .bottomMap(glm::vec2(0, 0), glm::vec2(10, 1))
                                               .leftMap(glm::vec2(0, 0), glm::vec2(1, 1))
                                               .rightMap(glm::vec2(0, 0), glm::vec2(1, 1))
                                               .build(),
                                       metalMaterial);
    mHandler->setPosition(glm::vec3(0, 14.0f, 0));

    mPress = std::make_shared<Model>(CylinderBuilder()
                                             .radius(2)
                                             .height(16)
                                             .sides(32)
                                             .wrap(glm::vec2(0, 0), glm::vec2(3, 5))
                                             .upperCap(glm::vec2(0, 0), glm::vec2(1, 1))
                                             .build(),
                                     brushedMaterial);
    mPress->setRotation(glm::vec3(-halfPI, 0, 0));
    mPress->setPosition(glm::vec3(0.0f, 12.7f, 0.0f));

    mTransportFront = std::make_shared<Model>(CylinderBuilder()
                                                      .radius(0.5)
                                                      .height(8)
                                                      .sides(32)
                                                      .wrap(glm::vec2(0, 0), glm::vec2(0.7, 1))
                                                      .upperCap(glm::vec2(0.7, 0), glm::vec2(0.7, 0.3))
                                                      .lowerCap(glm::vec2(0.7, 0), glm::vec2(0.7, 0.3))
                                                      .build(),
                                              conveyorMaterial);
    mTransportFront->setPosition(glm::vec3(0, 2, 15));
    mTransportFront->setRotation(glm::vec3(0, -halfPI, 0));

    mTransportBack = std::make_shared<Model>(CylinderBuilder()
                                                     .radius(0.5)
                                                     .height(8)
                                                     .sides(32)
                                                     .wrap(glm::vec2(0, 0), glm::vec2(0.7, 1))
                                                     .upperCap(glm::vec2(0.7, 0), glm::vec2(0.7, 0.3))
                                                     .lowerCap(glm::vec2(0.7, 0), glm::vec2(0.7, 0.3))
                                                     .build(),
                                             conveyorMaterial);
    mTransportBack->setPosition(glm::vec3(0, 2, -15));
    mTransportBack->setRotation(glm::vec3(0, -halfPI, 0));

    mTransportTop = std::make_shared<Model>(PlaneBuilder()
                                                    .width(8)
                                                    .height(30)
                                                    .mapping(glm::vec2(0, 0), glm::vec2(2, 5))
                                                    .build(),
                                            conveyorMaterial);
    mTransportTop->setRotation(glm::vec3(halfPI, 0, 0));
    mTransportTop->setPosition(glm::vec3(0, 2.5, 0));

    mTransportBottom = std::make_shared<Model>(PlaneBuilder()
                                                       .width(8)
                                                       .height(30)
                                                       .mapping(glm::vec2(0, 0), glm::vec2(2, 5))
                                                       .build(),
                                               conveyorMaterial);
    mTransportBottom->setRotation(glm::vec3(-halfPI, 0, 0));
    mTransportBottom->setPosition(glm::vec3(0, 1.5, 0));

    for (int i = 0; i < 1; ++i) {
        auto coin = std::make_shared<Model>(CylinderBuilder()
                                                    .radius(2)
                                                    .height(0.2)
                                                    .sides(60)
                                                    .wrap(glm::vec2(0.0, 0.47), glm::vec2(1, 0.49))
                                                    .upperCap(glm::vec2(0.5, 0.5), glm::vec2(1.0, 1.0))
                                                    .lowerCap(glm::vec2(0.0, 0.5), glm::vec2(0.5, 1.0))
                                                    .build(),
                                            coinBlankMaterial);
        coin->setRotation(glm::vec3(-halfPI, 0, 0));
        coin->setPosition(glm::vec3(0, 6, -12));
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
    mMainScene->addModel(mTransportBottom);


    for (auto&& coin : mCoins)
        mMainScene->addModel(coin);

    auto light = std::make_shared<DirectLight>(glm::vec3(0.5, -0.5, -0.5), glm::vec3(1.0, 1.0, 1.0), 1.2f);
//    mSpotLight = std::make_shared<PointLight>(glm::vec3(10, 12, 10), glm::vec3(0.5, 0.7, 0.8), 10.0f, 1.0f);
    mSpotLight = std::make_shared<SpotLight>(glm::vec3(0, 15, 0), glm::vec3(0, -1, 0), glm::vec3(1.0, 1.0, 1.0),
                                             glm::radians(12.5f), 10.0f, 3.0f);
    mMainScene->addLight(mSpotLight);
    mMainScene->addLight(light);
    coinBlankMaterial->setOpacity(0.0);

    for (GLuint i = 0; i < mCoins.size(); ++i) {

        auto coinAnimation = std::make_unique<AnimationSequence>();

        coinAnimation->addToSequence(std::make_shared<AnimationDelay>(5 * i));
        coinAnimation->addToSequence(std::make_shared<AnimationMaterialOpacity>(coinBlankMaterial, 1, 1.0f));
        coinAnimation->addToSequence(std::make_shared<AnimationModelMove>(mCoins[i], glm::vec3(0, -3.4, 0), 1));


        auto firstTransportAnimation = std::make_shared<AnimationConcurrent>();
        firstTransportAnimation->addAnimation(std::make_shared<AnimationModelMove>(mCoins[i], glm::vec3(0, 0, 12), 3));
        firstTransportAnimation->addAnimation(std::make_shared<AnimationTextureDisplacement>(conveyorMaterial, glm::vec2(0, -2), 3));

        coinAnimation->addToSequence(std::move(firstTransportAnimation));


        auto pressSequence = std::make_shared<AnimationSequence>();
        pressSequence->addToSequence(std::make_shared<AnimationModelMove>(mPress, -glm::vec3(0, 2, 0), 0.3));
        pressSequence->addToSequence(std::make_shared<AnimationDelay>(0.3));
        pressSequence->addToSequence(std::make_shared<AnimationModelMaterialSwap>(mCoins[i], coinPressedMaterial));
        pressSequence->addToSequence(std::make_shared<AnimationModelMove>(mPress, glm::vec3(0, 2, 0), 1.6));

        coinAnimation->addToSequence(std::move(pressSequence));

        auto secondTransportAnimation = std::make_shared<AnimationConcurrent>();
        secondTransportAnimation->addAnimation(std::make_shared<AnimationModelMove>(mCoins[i], glm::vec3(0, 0, 12), 3));
        secondTransportAnimation->addAnimation(std::make_shared<AnimationTextureDisplacement>(conveyorMaterial, glm::vec2(0, -2), 3));

        coinAnimation->addToSequence(std::move(secondTransportAnimation));
        coinAnimation->addToSequence(std::make_shared<AnimationMaterialOpacity>(coinPressedMaterial, 1, 0.0f));

        coinAnimation->setLooped(true);

        mAnimations.emplace_back(std::move(coinAnimation));
    }


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

    if (mWindow.isPressed(GLFW_KEY_PAGE_UP))
        mCameraDistance += 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_PAGE_DOWN))
        mCameraDistance -= 10 * cameraSpeed;


    if (mWindow.isPressed(GLFW_KEY_S))
        mLightPosition.z += 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_W))
        mLightPosition.z -= 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_D))
        mLightPosition.x += 10 * cameraSpeed;
    if (mWindow.isPressed(GLFW_KEY_A))
        mLightPosition.x -= 10 * cameraSpeed;

    mCameraPosition.x = (float) (mCameraDistance * cos(mCameraHAngle));
    mCameraPosition.y = (float) (mCameraDistance * sin(mCameraVAngle));
    mCameraPosition.z = (float) (mCameraDistance * sin(mCameraHAngle));

    for (auto&& anim : mAnimations)
        anim->animationStep(mDelta);

    mCamera->setPosition(mCameraPosition);
    mSpotLight->setTarget(mLightPosition);

    mSpotLight->setTarget(mCoins[0] -> getPosition());

    mRenderer.renderScene(mMainScene, mCamera);

    mWindow.swapBuffers();
    return !mWindow.isFinalize();
}


int main() {
    Main scene;
    while (scene.nextFrame());
    return 0;
}