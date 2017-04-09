#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CubeModel.h"
#include "GLSLProgramCompiler.h"
#include "Utils.h"
#include "Window.h"

using namespace std;

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

Window window(WIDTH, HEIGHT, "asd");

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

GLfloat pitch = 0.0f; // elewacja
const GLfloat pitch_max = 80.0f;
const GLfloat pitch_min = -80.0f;

GLfloat yaw = 0.0f; // azymut
const GLfloat yaw_max = 360.0f;
const GLfloat yaw_min = 0.0f;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat deltaTime = 0.0f;    // Time between current frame and last frame
GLfloat lastFrame = 0.0f;    // Time of last frame

void do_movement() {
    GLfloat cameraSpeed = 100.0f * deltaTime;
    if (window.isPressed(GLFW_KEY_UP))
        if ((pitch += cameraSpeed) > pitch_max)
            pitch = pitch_max;
    if (window.isPressed(GLFW_KEY_DOWN))
        if ((pitch -= cameraSpeed) < pitch_min)
            pitch = pitch_min;
    if (window.isPressed(GLFW_KEY_LEFT))
        if ((yaw -= cameraSpeed) < yaw_min)
            yaw += yaw_max;
    if (window.isPressed(GLFW_KEY_RIGHT))
        if ((yaw += cameraSpeed) > yaw_max)
            yaw -= yaw_max;
}


int main() {
    try {

        GLuint program = GLSLProgramCompiler::fromFiles("shaders/gl_06.vert", "shaders/gl_06.frag");

        CubeModel cube(1.0f);

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

        GLint modelLoc = glGetUniformLocation(program, "model");
        GLint viewLoc = glGetUniformLocation(program, "view");
        GLint projLoc = glGetUniformLocation(program, "projection");

        // set perspective projection & pass it to GPU
        glm::mat4 projection = glm::perspective(45.0f, (GLfloat) WIDTH / (GLfloat) HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // set view transformation & pass it to GPU
        glm::mat4 view;
        view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), cameraUp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


        // main event loop
        while (!window.isFinalize()) {
            GLfloat currentFrame = (GLfloat) glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            window.poolEvents();
            do_movement();

            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 trans;
            trans = glm::rotate(trans, pitch * 0.017f, glm::vec3(1, 0, 0));
            trans = glm::rotate(trans, yaw * 0.017f, glm::vec3(0, 1, 0));
            cube.Draw(trans, modelLoc);

            window.swapBuffers();
        }
    }
    catch (runtime_error e) {
        cout << e.what() << endl;
    }
    catch (exception ex) {
        cout << ex.what() << endl;
    }

    glfwTerminate();

    return 0;
}
