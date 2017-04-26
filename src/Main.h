#ifndef GKOM_INTRO_MAIN_H
#define GKOM_INTRO_MAIN_H

#include "Model/Model.h"

class Main {
private:
    Window mWindow;
    glm::mat4 mView;
    glm::mat4 mProjection;
    glm::vec3 mCameraPosition;
    GLfloat mDelta;
    GLfloat mLastFrame;
    GLfloat mCameraVAngle;
    GLfloat mCameraHAngle;
    GLfloat mCameraDistance;

    std::shared_ptr<Model> mCube;
    std::shared_ptr<Model> mCube2;

public:

    Main();

    bool nextFrame();
};


#endif //GKOM_INTRO_MAIN_H
