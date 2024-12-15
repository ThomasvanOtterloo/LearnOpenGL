#include "ElementBuffer.h"

ElementBuffer::ElementBuffer()
{
}

ElementBuffer::~ElementBuffer()
{
}

void ElementBuffer::CreateElementBuffer()
{
	glGenBuffers(1, &m_EBO);

}

void ElementBuffer::BindElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void ElementBuffer::AddIndices(unsigned int* indices, unsigned int size)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
