#pragma once
#include <vector>

namespace shapes
{
    struct Shape
    {
        float scaleX;
        float scaleY;
        float scaleZ;
        
        explicit Shape(float scaleX = 1.f, float scaleY = 1.f, float scaleZ = 1.f);
        
    protected:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        void applyScale();

    public:
        std::vector<float>& getVertices() { return vertices; }
        std::vector<unsigned int>& getIndices() { return indices; }
    };
}
