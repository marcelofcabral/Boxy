#include "Shape.h"

shapes::Shape::Shape(const float scaleX, const float scaleY, const float scaleZ) : scaleX{scaleX}, scaleY{scaleY},
    scaleZ{scaleZ}
{
}

void shapes::Shape::applyScale()
{
    if (scaleX != 1.f || scaleY != 1.f || scaleZ != 1.f)
    {
        for (int i = 0; i < vertices.size() / 3; i++)
        {
            vertices.at(i * static_cast<size_t>(3)) = scaleX * vertices.at(i * static_cast<size_t>(3));
            vertices.at(i * static_cast<size_t>(3) + 1) = scaleY * vertices.at(i * static_cast<size_t>(3) + 1);
            vertices.at(i * static_cast<size_t>(3) + 2) = scaleZ * vertices.at(i * static_cast<size_t>(3) + 2);
        }
    }
}
