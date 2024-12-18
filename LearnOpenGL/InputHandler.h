#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class InputHandler
{
private:
	GLFWwindow* window;
	float mixValue;

public:
	InputHandler(GLFWwindow* window);
	void processInput();
	float getMixValue() { return mixValue; }
};