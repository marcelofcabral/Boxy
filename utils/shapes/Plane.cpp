#include "Plane.h"

shapes::Plane::Plane(const float scaleX, const float scaleY, const float scaleZ) : Shape(scaleX, scaleY, scaleZ)
{
    vertices = {
        // bottom left
        -0.5f, -0.5f, 0.f,
        // up left
        -0.5f, 0.5f, 0.f,
        // up right
        0.5f, 0.5f, 0.f,
        // bottom right
        0.5f, -0.5f, 0.f,
    };

    indices = {
        0, 1, 2, // first triangle (bottom left, up left, up right)
        0, 2, 3 // second triangle (bottom left, up right, bottom right)
    };

    applyScale();
}
