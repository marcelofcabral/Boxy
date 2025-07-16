#include "ShaderProgram.h"

#include <iostream>
#include <glm/gtc/type_ptr.inl>

#include "../utils/FileHandling.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    const std::string vertexShaderCode{readShaderFile(vertexShaderPath)};
    const std::string fragmentShaderCode{readShaderFile(fragmentShaderPath)};

    const GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    const GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};

    compileShader(vertexShaderCode, vertexShader);
    compileShader(fragmentShaderCode, fragmentShader);

    id = glCreateProgram();

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    GLint linkingSuccess = GL_FALSE;
    char infoLog[512];

    glGetProgramiv(id, GL_LINK_STATUS, &linkingSuccess);

    if (!linkingSuccess)
    {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "Error linking program: " << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}

GLuint ShaderProgram::getId() const
{
    return id;
}

void ShaderProgram::use() const
{
    glUseProgram(id);
}

void ShaderProgram::setUniformBool(const std::string& uniformName, const bool value) const
{
    glUniform1i(glGetUniformLocation(id, uniformName.c_str()), static_cast<int>(value));
}

void ShaderProgram::setUniformInt(const std::string& uniformName, const int value) const
{
    glUniform1i(glGetUniformLocation(id, uniformName.c_str()), value);
}

void ShaderProgram::setUniformFloat(const std::string& uniformName, const float value) const
{
    glUniform1f(glGetUniformLocation(id, uniformName.c_str()), value);
}

void ShaderProgram::setUniformVec3f(const std::string& uniformName, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(id, uniformName.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniformMat4f(const std::string& uniformName, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(id, uniformName.c_str()), GL_FALSE, 1, glm::value_ptr(value));
}

std::string ShaderProgram::readShaderFile(const std::string& shaderFile)
{
    std::string shaderCode;

    try
    {
        shaderCode = readFile(shaderFile);
    }
    catch (std::ifstream::failure& error)
    {
        std::cout << "Error reading shader file: " << error.what() << '\n';
    }

    return shaderCode;
}

void ShaderProgram::compileShader(const std::string& shaderCode, const GLuint shaderId)
{
    GLint success = GL_FALSE;
    char infoLog[512];

    const GLchar* codePtr{shaderCode.c_str()};
    
    glShaderSource(shaderId, 1, &codePtr, nullptr);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        std::cout << "Error compiling shader: " << infoLog << '\n';
    }
}
