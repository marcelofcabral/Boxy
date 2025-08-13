#pragma once
#include <memory>
#include <set>

#include "../interfaces/IRenderable.h"
#include "../objects/Object.h"

class Camera;

class Scene : public IRenderable
{
private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Object> player;

    uint8_t projectileCount = 0;

    std::vector<std::shared_ptr<Object>> toBeRemoved;
    
public:
    explicit Scene(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Object>& player);
    
    void render() const override;
    void add(const std::shared_ptr<Object>& object);
    void tick();
    void markForRemoval(const std::shared_ptr<Object>& object);

    void syncSceneToCamera() const;

    void incrementProjectileCount();
    void decrementProjectileCount();
    void printProjectileCount() const;

private:
    std::set<std::shared_ptr<Object>> objects;

    void remove(const std::shared_ptr<Object>& object);
};
