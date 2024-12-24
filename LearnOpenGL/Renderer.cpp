#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"



Renderer::Renderer(GLFWwindow* window):window(window) {}

void Renderer::render()
{
	// Clear the screen with a specific color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}
