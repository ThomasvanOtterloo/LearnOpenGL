#pragma once

#include <glad/glad.h>

class ElementBuffer
{
private:
	unsigned int m_EBO;
public:
	ElementBuffer();
	~ElementBuffer();
	void CreateElementBuffer();
	void BindElementBuffer();
	void AddIndices(unsigned int* indices, unsigned int size);
};
