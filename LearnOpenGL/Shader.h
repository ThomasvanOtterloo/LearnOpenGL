#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers

class Shader
{
private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	void CheckShaderCompilation(unsigned int shader);
	void CheckShaderProgramCompilation(unsigned int shaderProgram);
	unsigned int shaderProgram;
public:
	// constructor reads and builds the shader
	Shader();
	~Shader();
	void CreateVertexShader(unsigned int id);
	void CreateFragmentShader(unsigned int id);
	void CreateShaderProgram();
	void UseShaderProgram();
	unsigned int GetShaderProgram();





};