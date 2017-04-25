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

    std::shared_ptr<Model> mCube;
public:
    Main();

    bool nextFrame();
};


#endif //GKOM_INTRO_MAIN_H
