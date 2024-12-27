#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>
#include <GLM/fwd.hpp>
#include <GLM/gtc/type_ptr.hpp>

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

	int GetUniformLocation(const char* uniformName);
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float X, float Y, float Z) const;





};