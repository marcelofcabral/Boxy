#pragma once
#include "Fighter.h"
#include "Object.h"

class Scene;

class Player final : public Fighter
{
private:
    static std::vector<float> colors;

public:
    explicit Player(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene);

    void shoot(const glm::vec3& direction);

    void takeDamage() override;
};
