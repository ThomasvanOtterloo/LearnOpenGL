#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>
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
	GLuint CreateVertexShader(std::string path);
	GLuint CreateFragmentShader(std::string path);
	void CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
	void UseShaderProgram();
	unsigned int GetShaderProgram();





};