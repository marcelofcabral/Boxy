#include "Object.h"

#include <vector>

Object::Object(const std::vector<float>& vertices, const std::vector<float>& colors,
               const std::vector<uint8_t>& indices, const std::string& vertexShaderSource,
               const std::string& fragmentShaderSource) : shaderProgram{vertexShaderSource, fragmentShaderSource}
{
    createVao(vertices, colors, indices);
}

Object::~Object()
{
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Object::createVao(const std::vector<float>& vertices, const std::vector<float>& colors,
                       const std::vector<uint8_t>& indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    numEboIndices = static_cast<GLsizei>(indices.size());

    glBindVertexArray(vao);

    // unifying vertex and colors for efficiency (no VBO switching)
    std::vector<float> verticesAndColors{vertices};
    verticesAndColors.insert(verticesAndColors.end(), colors.begin(), colors.end());

    // VBO binding
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesAndColors.size() * sizeof(float), verticesAndColors.data(), GL_STATIC_DRAW);

    // EBO binding
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint8_t), indices.data(), GL_STATIC_DRAW);

    // configuring vertex attribute pointer
    // for vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    // for colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          reinterpret_cast<void*>(vertices.size() * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::render() const
{
    glBindVertexArray(vao);
    glUseProgram(shaderProgram.getId());

    glDrawElements(GL_TRIANGLES, numEboIndices, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}
