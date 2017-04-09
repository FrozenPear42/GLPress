#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CubeModel.h"
#include "shprogram.h"

using namespace std;

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

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
    if (keys[GLFW_KEY_UP])
        if ((pitch += cameraSpeed) > pitch_max)
            pitch = pitch_max;
    if (keys[GLFW_KEY_DOWN])
        if ((pitch -= cameraSpeed) < pitch_min)
            pitch = pitch_min;
    if (keys[GLFW_KEY_LEFT])
        if ((yaw -= cameraSpeed) < yaw_min)
            yaw += yaw_max;
    if (keys[GLFW_KEY_RIGHT])
        if ((yaw += cameraSpeed) > yaw_max)
            yaw -= yaw_max;
}

GLuint LoadMipmapTexture(GLuint pTextureID, const char* pFile) {
    int width, height;
    unsigned char* image;
    GLuint texture;

    image = SOIL_load_image(pFile, &width, &height, 0, SOIL_LOAD_RGB);
    if (image == nullptr)
        throw runtime_error("Failed to load texture file: " + std::string(pFile));

    glGenTextures(1, &texture);
    glActiveTexture(pTextureID);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    return texture;
}

int main() {
    if (glfwInit() != GL_TRUE) {
        cout << "GLFW initialization failed" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    try {
        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Kocham GKOM <3<3<3", nullptr, nullptr);
        if (window == nullptr)
            throw runtime_error("GLFW window not created");
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, key_callback);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
            throw runtime_error("GLEW Initialization failed");

        glViewport(0, 0, WIDTH, HEIGHT);

        ShaderProgram theProgram("shaders/gl_06.vert", "shaders/gl_06.frag");

        CubeModel cube(1.0f);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "resources/iipw.png");
        GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "resources/weiti.png");

        glEnable(GL_DEPTH_TEST);

        theProgram.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture1"), 1);

        GLint modelLoc = glGetUniformLocation(theProgram.get_programID(), "model");
        GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
        GLint projLoc = glGetUniformLocation(theProgram.get_programID(), "projection");

        // set perspective projection & pass it to GPU
        glm::mat4 projection = glm::perspective(45.0f, (GLfloat) WIDTH / (GLfloat) HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // set view transformation & pass it to GPU
        glm::mat4 view;
        view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), cameraUp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // main event loop
        while (!glfwWindowShouldClose(window)) {
            GLfloat currentFrame = (GLfloat) glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glfwPollEvents();
            do_movement();

            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 trans;
            trans = glm::rotate(trans, pitch * 0.017f, glm::vec3(1, 0, 0));
            trans = glm::rotate(trans, yaw * 0.017f, glm::vec3(0, 1, 0));
            cube.Draw(trans, modelLoc);

            glfwSwapBuffers(window);
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
