#pragma once

class IRenderable
{
public:
    virtual void render() const = 0;

    virtual ~IRenderable() = default;
};
