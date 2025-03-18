#pragma once
#include "scripts/Script.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class RigidBody2D;

class MusicScript : public IScript
{
    struct BeatCircle
    {
        float spawnTime;
        float yPos;
        bool active;
    };

public:
    MusicScript() = default;

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

    void Render();

private:
    sf::Vector2f movement;

    const float SECONDS_PER_BEAT = 0.5f;
    const float TIMING_WINDOW = 0.1f;
    const float FALL_SPEED = 500.0f;
    sf::Clock beatClock;

    std::vector<sf::CircleShape> fallingCircles;
    sf::RectangleShape hitRect;
    sf::RenderWindow* window = nullptr;
};