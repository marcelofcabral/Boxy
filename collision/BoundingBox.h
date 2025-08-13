#pragma once
#include "../objects/Object.h"
#include "../utils/shapes/Cuboid.h"

class BoundingBox final : public Object
{
private:
    static shapes::Cuboid shape;
    static std::vector<float> colors;

    // used to draw the bounding box
    std::vector<float> vertices;

    // store pointer owner's model matrix to apply the same rotation when owner rotates
    glm::mat4* owningObjectModelMatrix = nullptr;
    
public:
    float minX;
    float minY;
    float minZ;

    float maxX;
    float maxY;
    float maxZ;

    bool shouldRecalculateMinMax = false;
    
    BoundingBox(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition);

    void render() override;

    void recalculateMinMax();
};
