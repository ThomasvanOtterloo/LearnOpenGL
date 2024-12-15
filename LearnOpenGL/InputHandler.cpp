#include <GLFW/glfw3.h>
#include <iostream>
#include "InputHandler.h"


InputHandler::InputHandler(GLFWwindow* window) : window(window) {}

void InputHandler::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
