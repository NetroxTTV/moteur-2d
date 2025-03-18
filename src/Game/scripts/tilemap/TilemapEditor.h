#pragma once
#include "scripts/Script.h"

class TilemapEditor : public IScript
{
private:
    sf::VertexArray gridVertices;
    
public:
    void OnStart() override;
    void OnUpdate() override;
    void OnRender(RenderWindow* window) override;
};
