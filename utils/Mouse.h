#pragma once
#include "Dimensions.h"

namespace mouse
{
    inline float x, y;

    inline float convertXToNdc()
    {
        return 2.f * x / static_cast<float>(Dimensions::WindowWidth) - 1.f;
    }

    inline float convertYToNdc()
    {
        return 1.f - 2.f * y / static_cast<float>(Dimensions::WindowHeight);
    }
}
