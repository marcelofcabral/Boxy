#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    static std::string viewMatrixUniformName;
    static std::string modelMatrixUniformName;
    static std::string projectionMatrixUniformName;
    
private:
    GLuint id;
    
public:
    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~ShaderProgram();

    GLuint getId() const;
    
    void use() const;

    void setUniformBool(const std::string& uniformName, bool value) const;
    void setUniformInt(const std::string& uniformName, int value) const;
    void setUniformFloat(const std::string& uniformName, float value) const;
    void setUniformVec3f(const std::string& uniformName, const glm::vec3& value);
    void setUniformMat4f(const std::string& uniformName, const glm::mat4& value);

private:
    std::string readShaderFile(const std::string& shaderFile);
    void compileShader(const std::string& shaderCode, GLuint shaderId);
};
