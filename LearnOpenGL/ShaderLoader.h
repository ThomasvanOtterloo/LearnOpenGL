#pragma once

#include <string>
#include <glad/glad.h> // include glad to get all the required OpenGL headers

class ShaderLoader
{
public:
	// constructor reads and builds the shader
	ShaderLoader();
	const GLchar* LoadShader(const std::string& file);

private:

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
};