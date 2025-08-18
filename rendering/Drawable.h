#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

#include "../shaders/ShaderProgram.h"

class Camera;


class Drawable
{
private:
    GLuint vao, ebo;
    GLsizei numEboIndices;
    
    void createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                   const std::vector<unsigned int>& indices);

protected:
    const std::vector<float>* colors;
    
    GLuint vbo;
    ShaderProgram shaderProgram;
    std::shared_ptr<Camera> camera;
    
    glm::mat4 modelMatrix{
        glm::translate(glm::mat4{1.f}, glm::vec3(0.0f, 0.0f, 0.0f))
    };

public:
    explicit Drawable(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                    const std::vector<float>& vertices, const std::vector<float>& colors,
                    const std::vector<unsigned int>& indices,
                    const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    
    virtual ~Drawable();
    
    virtual void render();

    virtual void tick() {}

    virtual void syncViewMatrixToCamera();

    void updateModelMatrix(const glm::mat4& newModelMatrix);
    void updateViewMatrix(const glm::mat4& newViewMatrix);
    void updateProjectionMatrix(const glm::mat4& newProjectionMatrix);

    ShaderProgram& getShaderProgram();
};
