#include "CollisionManager.h"

#include "BoundingBox.h"
#include "../objects/Object.h"

bool CollisionManager::checkForBoxCollision(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
    const BoundingBox aBox{a->getBoundingBox()};
    const BoundingBox bBox{b->getBoundingBox()};

    return aBox.minX <= bBox.maxX &&
        aBox.maxX >= bBox.minX &&
        aBox.minY <= bBox.maxY &&
        aBox.maxY >= bBox.minY &&
        aBox.minZ <= bBox.maxZ &&
        aBox.maxZ >= bBox.minZ;
}
