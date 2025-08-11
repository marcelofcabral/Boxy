#include "Object.h"

#include <vector>
#include <glm/ext/matrix_transform.hpp>

#include "Projectile.h"
#include "../camera/Camera.h"
#include "../utils/Logging.h"

Object::Object(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
               const std::vector<float>& vertices, const std::vector<float>& colors,
               const std::vector<unsigned int>& indices, const std::string& vertexShaderSource,
               const std::string& fragmentShaderSource) : shaderProgram{vertexShaderSource, fragmentShaderSource},
                                                          camera{camera}

{
    updateViewMatrix(camera->getViewMatrix());
    updateProjectionMatrix(camera->getProjectionMatrix());
    updateModelMatrix(glm::translate(modelMatrix, worldPosition));

    createVao(vertices, colors, indices);
}

Object::~Object()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Object::createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                       const std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    numEboIndices = static_cast<GLsizei>(indices.size());

    glBindVertexArray(vao);

    std::vector<float> verticesAndColors{vertices};
    verticesAndColors.insert(verticesAndColors.end(), colors.begin(), colors.end());

    logging::printVector(verticesAndColors);

    // VBO binding
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesAndColors.size() * sizeof(float), verticesAndColors.data(), GL_STATIC_DRAW);

    // EBO binding
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(vertices.size() * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::render() const
{
    shaderProgram.use();
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, numEboIndices, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Object::syncViewMatrixToCamera()
{
    updateViewMatrix(camera->getViewMatrix());
}

void Object::updateModelMatrix(const glm::mat4& newModelMatrix)
{
    modelMatrix = newModelMatrix;

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, newModelMatrix);
}

void Object::updateViewMatrix(const glm::mat4& newViewMatrix)
{
    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::viewMatrixUniformName, newViewMatrix);
}

void Object::updateProjectionMatrix(const glm::mat4& newProjectionMatrix)
{
    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::projectionMatrixUniformName, newProjectionMatrix);
}

void Object::move(const glm::vec3& direction)
{
    modelMatrix = glm::translate(modelMatrix, direction);

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);
}

void Object::rotate(const float angle, const glm::vec3& axis)
{
    modelMatrix = glm::rotate(modelMatrix, angle, axis);

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);
}

void Object::setRotation(const float angle, const glm::vec3& axis)
{
    glm::vec3 translation = glm::vec3(modelMatrix[3]);

    modelMatrix = glm::mat4{1.f};
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::rotate(modelMatrix, angle, axis);

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);
}

ShaderProgram& Object::getShaderProgram()
{
    return shaderProgram;
}

void Object::printPosition()
{
    std::cout << "Position: " << modelMatrix[3].x << " " << modelMatrix[3].y << " " << modelMatrix[3].z << '\n';
}
