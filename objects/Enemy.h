#pragma once
#include "Fighter.h"
#include "Object.h"

class Scene;

class Enemy final : public Fighter
{
private:
    static std::vector<float> colors;

    static float shotInterval;
    double lastShotTimestamp = 0.0;

    glm::vec3 movementDirection{math::getRandomUnitVectorOnXYPlane()};

public:
    explicit Enemy(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene,
                   const glm::vec3& worldPosition);

    void shoot(const glm::vec3& direction);

    void tick() override;
};
