#pragma once
#include <string>
#include <vector>
#include <optional>
#include <glad/glad.h>

#include "../interfaces/IRenderable.h"
#include "../shaders/ShaderProgram.h"

class Object : public IRenderable
{
private:
    GLuint vao, vbo, ebo;
    ShaderProgram shaderProgram;
    GLsizei numEboIndices;

    std::optional<glm::mat4> modelMatrixUpdate;
    std::optional<glm::mat4> viewMatrixUpdate;
    std::optional<glm::mat4> projectionMatrixUpdate;

public:
    Object(const std::vector<float>& vertices, const std::vector<float>& colors, const std::vector<unsigned int>& indices,
           const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    ~Object() override;

    void render() const override;
    
    void updateModelMatrix(const glm::mat4& newModelMatrix);
    void updateViewMatrix(const glm::mat4& newViewMatrix);
    void updateProjectionMatrix(const glm::mat4& newProjectionMatrix);

    ShaderProgram& getShaderProgram();

private:
    void createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                   const std::vector<unsigned int>& indices);
};
