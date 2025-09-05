#pragma once
#include "Object.h"

enum class ProjectileOrigin : uint8_t;
class Scene;

class Fighter : public Object, public std::enable_shared_from_this<Object>
{
private:
    static shapes::Cuboid shape;
    
protected:
    std::shared_ptr<Scene> scene;
    
public:
    uint8_t health;
    static float speed;

    explicit Fighter(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene, const std::vector<float>& colors,
                     const glm::vec3& worldPosition);

    bool move(const glm::vec3& direction);
    void shoot(const glm::vec3& direction, ProjectileOrigin projectileOrigin);

    void takeDamage();
};
