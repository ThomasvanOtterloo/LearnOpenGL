#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAOManager
{
private:
	unsigned int m_VAO;
	unsigned int* VAOs;

public:
	VAOManager(unsigned int size);
	~VAOManager();
	void BindVAO(unsigned int index = 0);
	void UnbindVAO();

	void SetAttributePointer(unsigned int index, 
		int size,
		unsigned int type,
		bool normalized,
		int stride, 
		void* pointer);
};
