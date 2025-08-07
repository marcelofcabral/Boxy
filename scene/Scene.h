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
    
public:
    explicit Scene(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Object>& player);
    
    void render() const override;
    
    void add(const std::shared_ptr<Object>& object);
    void remove(const std::shared_ptr<Object>& object);
    void tick() const;

    void syncSceneToCamera() const;
    

private:
    std::set<std::shared_ptr<Object>> objects;
};
