#pragma once
#include "Object.h"
#include "../utils/shapes/Cuboid.h"

class Projectile final : public Object
{
private:
    static shapes::Cuboid shape;
    static std::vector<float> colors;

    glm::vec3 direction;
    float projectileSpeed;

public:
    explicit Projectile(const std::shared_ptr<Camera>& camera, const glm::vec3& direction, 
                      const glm::vec3& worldPosition = glm::vec3(0.0f, 0.0f, 0.0f), 
                      float projectileSpeed = 5.f);

    void tick() override;
};
