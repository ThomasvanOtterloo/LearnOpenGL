#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"


class InputHandler
{
private:
	GLFWwindow* window;
	float mixValue;
	Camera camera;

public:
	InputHandler(GLFWwindow* window);
	void processInput();
	void processCameraInput(Camera& camera);
	float getMixValue() { return mixValue; }
};