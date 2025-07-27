#pragma once

#include "Shape.h"

namespace shapes
{
    struct Cuboid : Shape
    {
        explicit Cuboid(float scaleX = 1.f, float scaleY = 1.f, float scaleZ = 1.f);
    };
}
