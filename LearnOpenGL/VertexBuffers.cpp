#include "VertexBuffers.h"
#include <string>
#include <iostream>


VertexBuffers::VertexBuffers(unsigned int size)
{
    if (size > 1)
    {
        VBOs = new unsigned int[size];  // Dynamically allocate array
        glGenBuffers(size, VBOs);       // Generate multiple VBOs
    }
    else
    {
        VBOs = nullptr;                 // No array needed
        glGenBuffers(1, &VBO);          // Generate single VBO
    }
}

VertexBuffers::~VertexBuffers()
{
    if (VBOs)
    {
        delete[] VBOs;  // Free dynamically allocated array
    }
}


void VertexBuffers::BindVertexBuffers(GLenum type, unsigned int index)
{
    if (VBOs) {
        glBindBuffer(type, VBOs[index]);
    }
    else {
        glBindBuffer(type, VBO); // For single VBO case
    }

}

void VertexBuffers::AddVertices(float* vertices, size_t size)
{
	std::cout << "Size of vertrices : " << size << std::endl; // prints 8 because it was passed as a pointer... 
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}