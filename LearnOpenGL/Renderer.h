#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Renderer {
private:
	GLFWwindow* window;

public:
	Renderer(GLFWwindow* window);
	void render();
};