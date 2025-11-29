#pragma once
#include "Struct.h"
#include <vector>

class RenderComponent 
{
public:
    // RenderComponent(bool _render, const std::vector<Triangle>& _mesh)
    //     : render(_render), mesh(_mesh) {};
    RenderComponent(bool _render, const Triangle& _mesh)
        : render(_render), mesh(_mesh) {};
    RenderComponent() = default;
    ~RenderComponent() = default;

    bool render = false;
    //std::vector<Triangle> mesh;
    Triangle mesh;
    Vec2 Position = {0.0f, 0.0f};
    Vec2 scale = {1.0f, 1.0f};
};