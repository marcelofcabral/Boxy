#pragma once
#include <vector>
#include <glad/glad.h>

class Object
{
public:
    GLuint vao, vbo, ebo;

    void createVao(const std::vector<float>& vertices, const std::vector<uint8_t>& indices);
    void render();
};
