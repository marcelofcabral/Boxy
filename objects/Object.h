#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>

#include "../shaders/ShaderProgram.h"

class Object
{
private:
    GLuint vao, vbo, ebo;
    ShaderProgram shaderProgram;
    GLsizei numEboIndices;
    
public:
    Object(const std::vector<float>& vertices, const std::vector<float>& colors, const std::vector<uint8_t>& indices,
           const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    ~Object();
    
    void render() const;
    
private:
    void createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                   const std::vector<uint8_t>& indices);
};
