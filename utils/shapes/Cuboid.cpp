#include "Cuboid.h"

shapes::Cuboid::Cuboid(const float scaleX, const float scaleY, const float scaleZ) : Shape(scaleX, scaleY, scaleZ)
{
    vertices = {
        // bottom face
        -0.5f, 0.5f, 0.f, // 0
        0.5f, 0.5f, 0.f, // 1
        -0.5f, -0.5f, 0.f, // 2
        0.5f, -0.5f, 0.f, // 3

        // top face
        -0.5f, 0.5f, 1.f, // 4
        0.5f, 0.5f, 1.f, // 5
        -0.5f, -0.5f, 1.f, // 6
        0.5f, -0.5f, 1.f, // 7
    };

    indices = {
        // bottom face
        0, 1, 2,
        1, 2, 3,

        // top face
        4, 5, 6,
        5, 6, 7,

        // left face
        4, 6, 0,
        6, 0, 2,

        // right face
        5, 7, 1,
        7, 1, 3,

        // back face
        4, 5, 0,
        5, 0, 1,

        // front face
        6, 7, 2,
        7, 2, 3,
    };

    applyScale();
}