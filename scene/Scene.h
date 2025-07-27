#pragma once
#include <memory>
#include <set>

#include "../interfaces/IRenderable.h"
#include "../objects/Object.h"

class Scene : public IRenderable
{
public:
    void render() const override;
    
    void addRenderable(const std::shared_ptr<IRenderable>& renderable);
    void removeRenderable(const std::shared_ptr<IRenderable>& renderable);

private:
    std::set<std::shared_ptr<IRenderable>> renderables;
};
