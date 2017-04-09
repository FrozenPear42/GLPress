#include <GL/glew.h>
#include "Window.h"

Window::Window(unsigned int width, unsigned int height, std::string title) {
    if (glfwInit() != GL_TRUE)
        throw std::runtime_error("GLFW initialization failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (mWindow == nullptr)
        throw std::runtime_error("GLFW window not created");

    glfwMakeContextCurrent(mWindow);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW Initialization failed");

    glViewport(0, 0, width, height);
}


bool Window::isPressed(int keyCode) const {
    return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
}

bool Window::isFinalize() {
    return glfwWindowShouldClose(mWindow) != 0;
}

void Window::swapBuffers() {
    glfwSwapBuffers(mWindow);
}

void Window::poolEvents() {
    glfwPollEvents();
}

