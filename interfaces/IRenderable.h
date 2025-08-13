#pragma once

class IRenderable
{
public:
    virtual void render() = 0;

    virtual ~IRenderable() = default;
};
