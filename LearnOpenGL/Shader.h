#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

class Shader
{
public:
    unsigned int ID;

    // Constructor: Load, compile, and link shaders
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    {
        std::string vertexCode = readFile(vertexPath);
        std::string fragmentCode = readFile(fragmentPath);
        std::string geometryCode = geometryPath ? readFile(geometryPath) : "";

        ID = createShaderProgram(vertexCode.c_str(), fragmentCode.c_str(),
            geometryPath ? geometryCode.c_str() : nullptr);
    }

    // Activate the shader program
    void use() const
    {
        glUseProgram(ID);
    }

    // Uniform utility methods
    void setBool(const std::string& name, bool value) const { setUniform1i(name, static_cast<int>(value)); }
    void setInt(const std::string& name, int value) const { setUniform1i(name, value); }
    void setFloat(const std::string& name, float value) const { setUniform1f(name, value); }
    void setVec2(const std::string& name, const glm::vec2& value) const { setUniform2fv(name, value); }
    void setVec2(const std::string& name, float x, float y) const { setUniform2f(name, x, y); }
    void setVec3(const std::string& name, const glm::vec3& value) const { setUniform3fv(name, value); }
    void setVec3(const std::string& name, float x, float y, float z) const { setUniform3f(name, x, y, z); }
    void setVec4(const std::string& name, const glm::vec4& value) const { setUniform4fv(name, value); }
    void setVec4(const std::string& name, float x, float y, float z, float w) const { setUniform4f(name, x, y, z, w); }
    void setMat2(const std::string& name, const glm::mat2& mat) const { setUniformMatrix2fv(name, mat); }
    void setMat3(const std::string& name, const glm::mat3& mat) const { setUniformMatrix3fv(name, mat); }
    void setMat4(const std::string& name, const glm::mat4& mat) const { setUniformMatrix4fv(name, mat); }
	unsigned int getID() const { return ID; }

private:
    // Read file content
    std::string readFile(const std::string& filePath) const
    {
        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " + filePath);

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    // Create a shader program
    unsigned int createShaderProgram(const char* vertexCode, const char* fragmentCode, const char* geometryCode = nullptr)
    {
        unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode, "VERTEX");
        unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode, "FRAGMENT");

        unsigned int geometry = 0;
        if (geometryCode)
        {
            geometry = compileShader(GL_GEOMETRY_SHADER, geometryCode, "GEOMETRY");
        }

        unsigned int program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        if (geometryCode)
            glAttachShader(program, geometry);
        glLinkProgram(program);
        checkLinkErrors(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryCode)
            glDeleteShader(geometry);

        return program;
    }

    // Compile a shader
    unsigned int compileShader(GLenum shaderType, const char* shaderCode, const std::string& type)
    {
        unsigned int shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderCode, nullptr);
        glCompileShader(shader);
        checkCompileErrors(shader, type);
        return shader;
    }

    // Check shader compilation errors
    void checkCompileErrors(unsigned int shader, const std::string& type) const
    {
        int success;
        char infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            throw std::runtime_error("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog);
        }
    }

    // Check program linking errors
    void checkLinkErrors(unsigned int program) const
    {
        int success;
        char infoLog[1024];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 1024, nullptr, infoLog);
            throw std::runtime_error("ERROR::PROGRAM_LINKING_ERROR\n" + std::string(infoLog));
        }
    }

    // Uniform setters
    void setUniform1i(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
    void setUniform1f(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
    void setUniform2fv(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void setUniform2f(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); }
    void setUniform3fv(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void setUniform3f(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); }
    void setUniform4fv(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void setUniform4f(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
    void setUniformMatrix2fv(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void setUniformMatrix3fv(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void setUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
};

#endif
