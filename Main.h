#ifndef GKOM_INTRO_MAIN_H
#define GKOM_INTRO_MAIN_H

class Main {
private:
    Window mWindow;
    glm::mat4 mView;
    glm::mat4 mProjection;
    glm::vec3 mCameraPosition;
    GLfloat mDelta;
    GLfloat mLastFrame;

    CubeModel mCube;

    GLint mProjectionUniform;
    GLint mViewUniform;
    GLint mModelUniform;

public:
    Main();

    bool nextFrame();
};


#endif //GKOM_INTRO_MAIN_H
