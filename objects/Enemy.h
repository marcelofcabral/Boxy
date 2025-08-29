#pragma once
#include "Fighter.h"
#include "Object.h"

class Scene;

class Enemy final : public Fighter
{
private:
    static std::vector<float> colors;

public:
    static float enemySpeed;

    explicit Enemy(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene, const glm::vec3& worldPosition);

    void shoot(const glm::vec3& direction) override;
    
};
