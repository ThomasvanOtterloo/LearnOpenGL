#include "Shader.h"
#include "ShaderLoader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

Shader::Shader()
{
}

Shader::~Shader()
{
}

GLuint Shader::CreateVertexShader(std::string path)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Retrieve the shader source code from the file
	ShaderLoader shaderLoader;
	const GLchar* shaderSource = shaderLoader.LoadShader(path);
	
	// Attach the shader source code to the shader object
	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	delete[] shaderSource; // Don't forget to free the memory after use

	// Compile the shader
	glCompileShader(vertexShader);

	// check for shader compilation errors
	CheckShaderCompilation(vertexShader);

	return vertexShader;
}

GLuint Shader::CreateFragmentShader(std::string path)
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Retrieve the shader source code from the file
	ShaderLoader shaderLoader;
	const GLchar* shaderSource = shaderLoader.LoadShader(path);

	// Attach the shader source code to the shader object
	glShaderSource(fragmentShader, 1, &shaderSource, NULL);
	delete[] shaderSource; // Don't forget to free the memory after use

	// Compile the shader
	glCompileShader(fragmentShader);

	// check for shader compilation errors
	CheckShaderCompilation(fragmentShader);

	return fragmentShader;
}

void Shader::CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	shaderProgram = glCreateProgram();

	// Attach the shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link the shaders
	glLinkProgram(shaderProgram);

	// Check for linking errors
	CheckShaderProgramCompilation(shaderProgram);

	glDeleteShader(vertexShader); // since the shaders are linked to the shader program, we can delete them
	glDeleteShader(fragmentShader);
}

void Shader::UseShaderProgram()
{
	glUseProgram(shaderProgram);

}

unsigned int Shader::GetShaderProgram()
{
	return shaderProgram;
}

int Shader::GetUniformLocation(const char* uniformName)
{
	
	return glGetUniformLocation(shaderProgram, uniformName);
}

void Shader::CheckShaderCompilation(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::CheckShaderProgramCompilation(unsigned int shaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
