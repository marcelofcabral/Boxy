#pragma once

#include "Shape.h"

namespace shapes
{
    struct Plane : Shape
    {
        explicit Plane(float scaleX = 1.f, float scaleY = 1.f, float scaleZ = 1.f);
    };
}
