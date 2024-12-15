#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLFW/glfw3.h> // include glad to get all the required OpenGL headers



ShaderLoader::ShaderLoader()
{

}

const GLchar* ShaderLoader::LoadShader(const std::string& file)
{
    std::ifstream shaderFile(file);

	// Check if it can read the lines of the vertex.shader file
	if (!shaderFile.is_open())
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
    
  

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf(); // Read file content into stream
    shaderFile.close(); // Close the file

    // Store the content in a std::string
    std::string shaderCode = shaderStream.str();

    // Return the C-string version (GLchar is just a typedef for char)
    char* shaderSource = new char[shaderCode.size() + 1];
    strcpy_s(shaderSource, shaderCode.size() + 1, shaderCode.c_str());
    return shaderSource;
}