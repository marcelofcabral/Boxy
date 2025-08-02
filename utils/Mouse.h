#pragma once
#include "Dimensions.h"

namespace mouse
{
    inline float x, y;
    
    static inline bool leftButtonClicked = false;

    inline bool getLmbClicked()
    {
        if (leftButtonClicked)
        {
            leftButtonClicked = false;
            return true;
        }
        
        return false;
    }

    inline void setLmbClicked(const bool state)
    {
        leftButtonClicked = state;
    }
    
    inline float convertXToNdc()
    {
        return 2.f * x / static_cast<float>(Dimensions::WindowWidth) - 1.f;
    }

    inline float convertYToNdc()
    {
        return 1.f - 2.f * y / static_cast<float>(Dimensions::WindowHeight);
    }
}
