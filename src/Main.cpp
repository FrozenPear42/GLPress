#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils/GLSLProgramCompiler.h"
#include "Utils/Utils.h"
#include "Utils/Window.h"
#include "Main.h"

GLfloat pitch = 0.0f;
const GLfloat pitch_max = 80.0f;
const GLfloat pitch_min = -80.0f;

GLfloat yaw = 0.0f;
const GLfloat yaw_max = 360.0f;
const GLfloat yaw_min = 0.0f;


Main::Main() : mWindow(800, 600, "Kocham GKOM <3"),
               mCameraPosition(0.0f, 0.0f, 3.0f),
               mDelta(0.0f),
               mLastFrame(0.0f) {
    mView = glm::lookAt(mCameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mProjection = glm::perspective(45.0f, (GLfloat) 800 / 600, 0.1f, 100.0f);

    GLuint program = GLSLProgramCompiler::fromFiles("shaders/gl_06.vert", "shaders/gl_06.frag");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLuint texture0 = Utils::mipmapTextureFromFile(GL_TEXTURE0, "resources/iipw.png");
    GLuint texture1 = Utils::mipmapTextureFromFile(GL_TEXTURE1, "resources/weiti.png");

    glEnable(GL_DEPTH_TEST);

    glUseProgram(program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glUniform1i(glGetUniformLocation(program, "Texture0"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(program, "Texture1"), 1);

    mModelUniform = glGetUniformLocation(program, "model");
    mViewUniform = glGetUniformLocation(program, "view");
    mProjectionUniform = glGetUniformLocation(program, "projection");

    glUniformMatrix4fv(mProjectionUniform, 1, GL_FALSE, glm::value_ptr(mProjection));
    glUniformMatrix4fv(mViewUniform, 1, GL_FALSE, glm::value_ptr(mView));

    mCube = std::make_shared<Model>(Mesh::loadFromObjFile("resources/cube.obj"), std::make_shared<Material>("resources/materials/", "metal"));
//    mCube = std::make_shared<Model>(Mesh::loadFromFile("resources/cube.mesh"), std::make_shared<Material>());

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
    mCube->draw();

    mWindow.swapBuffers();
    return !mWindow.isFinalize();
}


int main() {
    Main scene;
    while (scene.nextFrame());
    return 0;
}