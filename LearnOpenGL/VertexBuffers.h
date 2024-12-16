#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffers
{
public:
	VertexBuffers(unsigned int size);
	~VertexBuffers();



	void BindVertexBuffers(GLenum type, unsigned int index = 0);
	void AddVertices(float* vertices, size_t size);


private:
	unsigned int VBO;      // If size == 1, use this single VBO.
	unsigned int* VBOs;    // Pointer to array of VBOs when size > 1.

};