#include "VAOManager.h"

VAOManager::VAOManager()
{

}

VAOManager::~VAOManager()
{
}

void VAOManager::CreateVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
}

void VAOManager::BindVAO()
{
	glBindVertexArray(m_VAO);
}

void VAOManager::UnbindVAO()
{
}

void VAOManager::SetAttributePointer(unsigned int index, int size, unsigned int type, bool normalized, int stride, void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

