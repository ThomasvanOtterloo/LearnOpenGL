#include "VertexBuffers.h"


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

void VertexBuffers::AddVertices(float* vertices)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}