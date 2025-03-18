#pragma once
#include "ECS/Components/Component.h"

class Sprite;

class ProgressBar: public Component
{
public:
    static constexpr int BITMASK = 1 << 7;
    
    ProgressBar(Entity* entity, Sprite* background, Sprite* progressBar);
    ~ProgressBar() override = default;
    int GetBitmask() override;

    Sprite* BackgroundImage;
    Sprite* Bar;
};
