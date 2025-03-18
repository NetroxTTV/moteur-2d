#pragma once
#include "Managers/Scene.h"

class Editor : public Scene
{
    void OnEnter() override;
    void Render() override;

public:
    void OnFixedUpdate() override {};
    void OnUpdate() override {};
    void OnExit() override {};
};
