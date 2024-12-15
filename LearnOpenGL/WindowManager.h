#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
private:
    GLFWwindow* window;

public:
    bool init(int width, int height, const char* title);
    GLFWwindow* getWindow() const;
    bool shouldClose() const;
    void swapBuffersAndPollEvents();
    ~WindowManager();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
