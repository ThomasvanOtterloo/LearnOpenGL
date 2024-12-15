#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffers
{
public:
	VertexBuffers(unsigned int size);

	/*template <typename T>
	void CreateBuffers(unsigned int amount) {
		if (size > 0)
		{
			glGenBuffers(size, &VBO);
		}
		else
		{
			glGenBuffers(1, &VBO);
		}
	}*/

	void BindVertexBuffers(GLenum type);
	void AddVertices(float* vertices, size_t size);


private:
	unsigned int VBO;
};