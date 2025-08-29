#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "BoundingBox.h"

class BoundingBox;
class Object;

class CollisionManager
{
private:
    static MinMaxes getMinMaxesInWorldSpace(const BoundingBox& localBox, const glm::mat4& modelMatrix);
public:
    static bool checkForBoxCollision(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b);
};
