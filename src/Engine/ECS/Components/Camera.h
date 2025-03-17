#pragma once
#include "Component.h"

class Camera : public Component
{
public:
    static constexpr int BITMASK = 1 << 3;
    
    Camera(Entity* entity);
    ~Camera();
    int GetBitmask() override;
};
