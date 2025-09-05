#pragma once
#include "Object.h"
#include "../utils/shapes/Cuboid.h"

class Wall final : public Object
{
private:
    static shapes::Cuboid shape;
    static std::vector<float> colors;

public:
    explicit Wall(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition, float rotation);
};