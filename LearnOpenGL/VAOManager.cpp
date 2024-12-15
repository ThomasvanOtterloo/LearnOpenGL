#include "VAOManager.h"

VAOManager::VAOManager(unsigned int size)
{
	if (size > 1)
	{
		VAOs = new unsigned int[size];  // Dynamically allocate array
		glGenVertexArrays(size, VAOs);       // Generate multiple VAOs
	}
	else
	{
		VAOs = nullptr;                 // No array needed
		glGenVertexArrays(1, &m_VAO);          // Generate single VAO
	}

}

VAOManager::~VAOManager()
{
}

void VAOManager::BindVAO(unsigned int index)
{
	if (VAOs) {
		glBindVertexArray(VAOs[index]);
	}
	else {
		glBindVertexArray(m_VAO); // For single VAO case
	}
}

void VAOManager::UnbindVAO()
{
}

void VAOManager::SetAttributePointer(unsigned int index, int size, unsigned int type, bool normalized, int stride, void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

