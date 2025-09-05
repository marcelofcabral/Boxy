#include "CollisionManager.h"

#include <iostream>

#include "BoundingBox.h"
#include "../objects/Object.h"
#include "../objects/Obstacle.h"

MinMaxes CollisionManager::getMinMaxesInWorldSpace(const BoundingBox& localBox, const glm::mat4& modelMatrix)
{
    constexpr float maxFloat = std::numeric_limits<float>::max();
    constexpr float minFloat = std::numeric_limits<float>::lowest();

    MinMaxes worldMinMaxes{maxFloat, maxFloat, maxFloat, minFloat, minFloat, minFloat};

    std::vector vertices{
        glm::vec4{localBox.minMaxes.minX, localBox.minMaxes.minY, localBox.minMaxes.minZ, 1.0f},
        glm::vec4{localBox.minMaxes.maxX, localBox.minMaxes.minY, localBox.minMaxes.minZ, 1.0f},
        glm::vec4{localBox.minMaxes.minX, localBox.minMaxes.maxY, localBox.minMaxes.minZ, 1.0f},
        glm::vec4{localBox.minMaxes.maxX, localBox.minMaxes.maxY, localBox.minMaxes.minZ, 1.0f},
        glm::vec4{localBox.minMaxes.minX, localBox.minMaxes.minY, localBox.minMaxes.maxZ, 1.0f},
        glm::vec4{localBox.minMaxes.maxX, localBox.minMaxes.minY, localBox.minMaxes.maxZ, 1.0f},
        glm::vec4{localBox.minMaxes.minX, localBox.minMaxes.maxY, localBox.minMaxes.maxZ, 1.0f},
        glm::vec4{localBox.minMaxes.maxX, localBox.minMaxes.maxY, localBox.minMaxes.maxZ, 1.0f}
    };

    for (glm::vec4& vertex : vertices)
    {
        glm::vec4 worldVertex = modelMatrix * vertex;

        worldMinMaxes.minX = std::min(worldMinMaxes.minX, worldVertex.x);
        worldMinMaxes.minY = std::min(worldMinMaxes.minY, worldVertex.y);
        worldMinMaxes.minZ = std::min(worldMinMaxes.minZ, worldVertex.z);

        worldMinMaxes.maxX = std::max(worldMinMaxes.maxX, worldVertex.x);
        worldMinMaxes.maxY = std::max(worldMinMaxes.maxY, worldVertex.y);
        worldMinMaxes.maxZ = std::max(worldMinMaxes.maxZ, worldVertex.z);
    }

    return worldMinMaxes;
}

bool CollisionManager::checkForBoxCollision(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
    const MinMaxes aBoxWorldMinMaxes{getMinMaxesInWorldSpace(a->getBoundingBox(), a->getModelMatrix())};
    const MinMaxes bBoxWorldMinMaxes{getMinMaxesInWorldSpace(b->getBoundingBox(), b->getModelMatrix())};

    const bool result{
        aBoxWorldMinMaxes.minX <= bBoxWorldMinMaxes.maxX &&
        aBoxWorldMinMaxes.maxX >= bBoxWorldMinMaxes.minX &&
        aBoxWorldMinMaxes.minY <= bBoxWorldMinMaxes.maxY &&
        aBoxWorldMinMaxes.maxY >= bBoxWorldMinMaxes.minY &&
        aBoxWorldMinMaxes.minZ <= bBoxWorldMinMaxes.maxZ &&
        aBoxWorldMinMaxes.maxZ >= bBoxWorldMinMaxes.minZ
    };

    if (result)
    {
        std::cout << "Collision between " << a->id << " and " << b->id << '\n';
        std::cout << "Object " << a->id << " bounds: min(" << aBoxWorldMinMaxes.minX << ", " << aBoxWorldMinMaxes.minY << ", " << aBoxWorldMinMaxes.minZ 
                  << ") max(" << aBoxWorldMinMaxes.maxX << ", " << aBoxWorldMinMaxes.maxY << ", " << aBoxWorldMinMaxes.maxZ << ")\n";
        std::cout << "Object " << b->id << " bounds: min(" << bBoxWorldMinMaxes.minX << ", " << bBoxWorldMinMaxes.minY << ", " << bBoxWorldMinMaxes.minZ 
                  << ") max(" << bBoxWorldMinMaxes.maxX << ", " << bBoxWorldMinMaxes.maxY << ", " << bBoxWorldMinMaxes.maxZ << ")\n";
    }

    return result;
}
