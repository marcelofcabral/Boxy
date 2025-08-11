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

    glm::mat4 modelMatrix{
        glm::translate(glm::mat4{1.f}, glm::vec3(0.0f, 0.0f, 0.0f))
    };

protected:
    std::shared_ptr<Camera> camera;

    /*
    std::optional<glm::mat4> modelMatrixUpdate;
    std::optional<glm::mat4> viewMatrixUpdate;
    std::optional<glm::mat4> projectionMatrixUpdate;
    */
public:
    explicit Object(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                    const std::vector<float>& vertices, const std::vector<float>& colors,
                    const std::vector<unsigned int>& indices,
                    const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    ~Object() override;

    void render() const override;

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

    void printPosition();

private:
    void createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                   const std::vector<unsigned int>& indices);
};
