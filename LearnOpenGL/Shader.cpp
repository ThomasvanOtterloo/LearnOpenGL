#include "Shader.h"
#include "ShaderLoader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::CreateVertexShader(unsigned int id)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);


	// Retrieve the shader source code from the file
	ShaderLoader shaderLoader;
	const GLchar* shaderSource = shaderLoader.LoadShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Vertex.shader");
	
	// Attach the shader source code to the shader object
	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	delete[] shaderSource; // Don't forget to free the memory after use

	// Compile the shader
	glCompileShader(vertexShader);

	// check for shader compilation errors
	CheckShaderCompilation(vertexShader);
}

void Shader::CreateFragmentShader(unsigned int id)
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Retrieve the shader source code from the file
	ShaderLoader shaderLoader;
	const GLchar* shaderSource = shaderLoader.LoadShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Fragment.shader");

	// Attach the shader source code to the shader object
	glShaderSource(fragmentShader, 1, &shaderSource, NULL);
	delete[] shaderSource; // Don't forget to free the memory after use

	// Compile the shader
	glCompileShader(fragmentShader);

	// check for shader compilation errors
	CheckShaderCompilation(fragmentShader);
}

void Shader::CreateShaderProgram()
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

	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Program Linking Error: " << infoLog << std::endl;
	}
}

unsigned int Shader::GetShaderProgram()
{
	return shaderProgram;
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
