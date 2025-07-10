#pragma once
#include <vector>

struct Rectangle
{
    static std::vector<float> getVertices() { return vertices; }
    static std::vector<uint8_t> getIndices() { return indices; }
    
private:
    static std::vector<float> vertices; // 8 vertices, 3 coordinates (x, y, z) for each: 8 * 3 = 24
    static std::vector<uint8_t> indices; // 6 faces, 2 triangles for each face, 3 vertices for each triangle: 6 * 2 * 3 = 36
};
