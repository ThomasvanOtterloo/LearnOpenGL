#include <iostream>
#include "InputHandler.h"
#include <string>
#include "Camera.h"




InputHandler::InputHandler(GLFWwindow* window, Camera& cam) : window(window), camera(cam) {}

void InputHandler::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, InputHandler::mouse_callback);
    // In your InputHandler.cpp or wherever you initialize GLFW callbacks
    glfwSetScrollCallback(window, InputHandler::scroll_callback);

}

void InputHandler::processCameraInput(float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}


// This static function is what GLFW will call whenever the mouse moves.
// It just forwards the call to the actual member function.
void InputHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Retrieve the 'this' pointer we stored in the constructor
    InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
    if (handler)
    {
        handler->handleMouseMovement(xpos, ypos);
    }
}


void InputHandler::handleMouseMovement(double xpos, double ypos)
{
    auto* inputHandler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
    if (!inputHandler) return; // Safety check
	std::cout << "Mouse moved to (" << xpos << ", " << ypos << ")" << std::endl;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}



// InputHandler.cpp
void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Retrieve the 'this' pointer from window user pointer
    InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
    if (handler)
    {
        handler->handleMouseScroll(xoffset, yoffset);
    }
}

void InputHandler::handleMouseScroll(double xoffset, double yoffset)
{
    // If you have a reference/pointer to your main camera:
    camera.ProcessMouseScroll((float)yoffset);
    // xoffset is usually horizontal scrolling, which is typically ignored for zoom.
}



