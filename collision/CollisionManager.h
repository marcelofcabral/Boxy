#pragma once
#include <memory>

class Object;

class CollisionManager
{
public:
    static bool checkForBoxCollision(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b);
};
