#pragma once
#include "Object.h"
#include "../camera/Camera.h"
#include "../utils/shapes/Cuboid.h"

class Scene;

enum class ProjectileOrigin : uint8_t
{
    Player,
    Enemy
};

class Projectile final : public Object, public std::enable_shared_from_this<Projectile>
{
private:
    static shapes::Cuboid shape;
    static std::vector<float> colors;
    std::shared_ptr<Scene> scene;

    glm::vec3 direction;
    float projectileSpeed;

public:
    explicit Projectile(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene,
                        const glm::vec3& direction,
                        const glm::vec3& worldPosition,
                        ProjectileOrigin origin, float projectileSpeed = 17.5f);

    void tick() override;

    ProjectileOrigin origin;
};
