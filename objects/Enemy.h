#pragma once
#include "Object.h"

class Enemy final : public Object
{
private:
    static shapes::Cuboid shape;
    static std::vector<float> colors;

public:
    static float enemySpeed;

    explicit Enemy(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition);
    
};
