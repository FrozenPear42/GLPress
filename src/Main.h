#ifndef GKOM_INTRO_MAIN_H
#define GKOM_INTRO_MAIN_H

#include "Model/Model.h"
#include "Camera/Camera.h"
#include "Renderer.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"

class Main {
private:
    Window mWindow;
    glm::vec3 mCameraPosition;
    glm::vec3 mLightPosition;

    GLfloat mDelta;
    GLfloat mLastFrame;
    GLfloat mCameraVAngle;
    GLfloat mCameraHAngle;
    GLfloat mCameraDistance;

    Renderer mRenderer;
    std::shared_ptr<Scene> mMainScene;
    std::shared_ptr<Camera> mCamera;

    std::shared_ptr<Model> mBase;
    std::shared_ptr<Model> mColumnRight;
    std::shared_ptr<Model> mColumnLeft;
    std::shared_ptr<Model> mHandler;

    std::shared_ptr<Model> mTransportFront;
    std::shared_ptr<Model> mTransportBack;

    std::shared_ptr<Model> mTransportTop;
    std::shared_ptr<Model> mTransportBottom;

    std::shared_ptr<Model> mPress;

    std::shared_ptr<SpotLight> mSpotLight;

    std::shared_ptr<Skybox> mSkybox;

public:
    Main();

    bool nextFrame();
};


#endif //GKOM_INTRO_MAIN_H
