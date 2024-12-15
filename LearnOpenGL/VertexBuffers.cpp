#include "VertexBuffers.h"
#include <string>
#include <iostream>


VertexBuffers::VertexBuffers(unsigned int size)
{
	if (size > 1)
	{
		glGenBuffers(size, &VBO);
	}
	else
	{
		glGenBuffers(1, &VBO);
	}
}


void VertexBuffers::BindVertexBuffers(GLenum type)
{
	glBindBuffer(type, VBO);
}

void VertexBuffers::AddVertices(float* vertices, size_t size)
{
	std::cout << "Size of vertrices : " << sizeof(vertices) << std::endl; // prints 8 because it was passed as a pointer... 
	std::cout << " vertrices pointer looked like..: " << vertices << std::endl; //  0000 00A7 28BA F998

	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}