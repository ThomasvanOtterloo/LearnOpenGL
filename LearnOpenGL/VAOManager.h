#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAOManager
{
private:
	unsigned int m_VAO;

public:
	VAOManager();
	~VAOManager();
	void CreateVAO();
	void BindVAO();
	void UnbindVAO();

	void SetAttributePointer(unsigned int index, 
		int size,
		unsigned int type,
		bool normalized,
		int stride, 
		void* pointer);
};
