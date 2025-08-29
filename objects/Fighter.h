#pragma once
#include "Object.h"

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

    void move(const glm::vec3& direction);
    virtual void shoot(const glm::vec3& direction) = 0;

    void takeDamage();
    
    void rotate(float angle, const glm::vec3& axis);
    void setRotation(float angle, const glm::vec3& axis);
};
