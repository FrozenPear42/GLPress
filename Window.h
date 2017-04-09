#ifndef GLPRESS_WINDOW_H
#define GLPRESS_WINDOW_H

#include <GLFW/glfw3.h>
#include <functional>

class Window {
private:
    GLFWwindow* mWindow;

public:
    Window(unsigned int width, unsigned int height, std::string title);

    bool isPressed(int keyCode) const;

    bool isFinalize();

    void swapBuffers();

    void poolEvents();
};

#endif //GLPRESS_WINDOW_H
