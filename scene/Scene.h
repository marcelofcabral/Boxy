#pragma once
#include <memory>
#include <set>

#include "../interfaces/IRenderable.h"
#include "../objects/Object.h"

class Scene : public IRenderable
{
public:
    void render() const override;
    
    void add(const std::shared_ptr<Object>& object);
    void remove(const std::shared_ptr<Object>& object);

    void updateViewMatrix(const glm::mat4& viewMatrix, const std::set<std::shared_ptr<Object>>& except);
    

private:
    std::set<std::shared_ptr<Object>> objects;
};
