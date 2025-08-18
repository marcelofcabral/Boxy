#include "Drawable.h"

#include <vector>
#include <glm/ext/matrix_transform.hpp>

#include "../camera/Camera.h"
#include "../utils/Logging.h"

Drawable::Drawable(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                   const std::vector<float>& vertices, const std::vector<float>& colors,
                   const std::vector<unsigned int>& indices, const std::string& vertexShaderSource,
                   const std::string& fragmentShaderSource) : colors{&colors},
                                                              shaderProgram{vertexShaderSource, fragmentShaderSource}, camera{camera}
{
    updateViewMatrix(camera->getViewMatrix());
    updateProjectionMatrix(camera->getProjectionMatrix());
    updateModelMatrix(glm::translate(modelMatrix, worldPosition));

    createVao(vertices, colors, indices);
}

Drawable::~Drawable()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Drawable::createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                         const std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    numEboIndices = static_cast<GLsizei>(indices.size());

    glBindVertexArray(vao);

    std::vector<float> verticesAndColors{vertices};
    verticesAndColors.insert(verticesAndColors.end(), colors.begin(), colors.end());

    std::cout << "Vertices" << '\n';
    logging::printVector(vertices);

    std::cout << "Colors" << '\n';
    logging::printVector(colors);

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

void Drawable::render()
{
    shaderProgram.use();
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, numEboIndices, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Drawable::syncViewMatrixToCamera()
{
    updateViewMatrix(camera->getViewMatrix());
}

void Drawable::updateModelMatrix(const glm::mat4& newModelMatrix)
{
    modelMatrix = newModelMatrix;

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, newModelMatrix);
}

void Drawable::updateViewMatrix(const glm::mat4& newViewMatrix)
{
    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::viewMatrixUniformName, newViewMatrix);
}

void Drawable::updateProjectionMatrix(const glm::mat4& newProjectionMatrix)
{
    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::projectionMatrixUniformName, newProjectionMatrix);
}

ShaderProgram& Drawable::getShaderProgram()
{
    return shaderProgram;
}
