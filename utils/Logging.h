#pragma once
#include <iomanip>
#include <iostream>
#include <vector>

namespace logging
{
    inline void printVector(const std::vector<float>& vector)
    {
        std::cout << '[';
        
        for (auto item : vector)
        {
            std::cout << std::fixed << std::setprecision(1) << item << " ";
        }
        
        std::cout << ']' << '\n';
    }
}
