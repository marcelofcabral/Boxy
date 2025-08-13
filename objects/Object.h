#pragma once
#include <string>
#include <vector>
// #include <optional>
#include <memory>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

#include "../interfaces/IRenderable.h"
#include "../shaders/ShaderProgram.h"

class Camera;

class Object : public IRenderable
{
private:
    GLuint vao, vbo, ebo;
    ShaderProgram shaderProgram;
    GLsizei numEboIndices;

protected:
    std::shared_ptr<Camera> camera;

    glm::mat4 modelMatrix{
        glm::translate(glm::mat4{1.f}, glm::vec3(0.0f, 0.0f, 0.0f))
    };

private:
    void createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                   const std::vector<unsigned int>& indices);

public:
    explicit Object(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                    const std::vector<float>& vertices, const std::vector<float>& colors,
                    const std::vector<unsigned int>& indices,
                    const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    ~Object() override;

    void render() override;

    bool shouldTick = true;

    virtual void tick()
    {
    }

    void syncViewMatrixToCamera();

    void updateModelMatrix(const glm::mat4& newModelMatrix);
    void updateViewMatrix(const glm::mat4& newViewMatrix);
    void updateProjectionMatrix(const glm::mat4& newProjectionMatrix);

    void move(const glm::vec3& direction);
    void rotate(float angle, const glm::vec3& axis);
    void setRotation(float angle, const glm::vec3& axis);

    ShaderProgram& getShaderProgram();

    glm::vec3 getPosition();

    void printPosition();
};
