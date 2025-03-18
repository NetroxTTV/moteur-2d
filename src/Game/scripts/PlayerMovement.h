#pragma once
#include "scripts/Script.h"

class RigidBody2D;

class PlayerMovement : public IScript
{
    
public:
    PlayerMovement() = default;
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

	const float SECONDS_PER_BEAT = 0.5f;
	const float TIMING_WINDOW = 0.1f;
	sf::Clock beatClock;
};
