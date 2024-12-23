#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"


class InputHandler
{
private:
	GLFWwindow* window;
	float mixValue;
	Camera& camera;
	float lastX = 400, lastY = 300;
	bool firstMouse = true;
	float yaw = -90.0f;
	float pitch = 0.0f;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
	InputHandler(GLFWwindow* window, Camera& camera);
	void processInput();
	void processCameraInput(float deltaTime);
	float getMixValue() { return mixValue; }
	void handleMouseMovement(double xpos, double ypos);
	void handleMouseScroll(double xoffset, double yoffset);


};