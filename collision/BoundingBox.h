#pragma once
#include "../utils/shapes/Cuboid.h"
#include "../camera/Camera.h"
#include "../rendering/Drawable.h"

typedef struct MinMaxes
{
    float minX, minY, minZ, maxX, maxY, maxZ;

    MinMaxes(float minX = 0.f, float minY = 0.f, float minZ = 0.f, float maxX = 0.f, float maxY = 0.f,
             float maxZ = 0.f) : minX{minX}, minY{minY},
                                 minZ{minZ}, maxX{maxX}, maxY{maxY}, maxZ{maxZ}
    {
    }
} MinMaxes;

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
    MinMaxes minMaxes;

    bool shouldRecalculateMinMax = false;

    BoundingBox(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                const glm::mat4* owningObjectModelMatrix, shapes::Cuboid& shape);

    void render() override;

    void recalculateMinMax();

    void updatePositionToMatchOwner();
};
