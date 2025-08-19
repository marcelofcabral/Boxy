#pragma once
#include "../utils/shapes/Cuboid.h"
#include "../camera/Camera.h"
#include "../rendering/Drawable.h"

class BoundingBox final : public Drawable
{
private:
    static std::vector<float> colors;

    // used to draw the bounding box
    std::vector<float> originalVertices;
    std::vector<float> vertices;

    // store pointer owner's model matrix to apply the same rotation when owner rotates
    const glm::mat4* owningObjectModelMatrix = nullptr;
    
public:
    float minX;
    float minY;
    float minZ;

    float maxX;
    float maxY;
    float maxZ;

    bool shouldRecalculateMinMax = false;
    
    BoundingBox(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition, const glm::mat4* owningObjectModelMatrix, shapes::Cuboid& shape);

    void render() override;

    void recalculateMinMax();

    void updatePositionToMatchOwner();
};
