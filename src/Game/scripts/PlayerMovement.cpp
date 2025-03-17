#include "pch.h"
#include "PlayerMovement.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "Managers/InputManager.h"
#include <SFML/Audio.hpp>

void PlayerMovement::OnStart()
{
    if (!music.openFromFile("../../res/Music/musique.mp3"))
    {
        std::cerr << "Error loading musique.mp3" << std::endl;
        return;
    }

    music.play();
    beatClock.restart();
}

void PlayerMovement::OnFixedUpdate()
{
}

void PlayerMovement::OnUpdate()
{
    float currentTime = beatClock.getElapsedTime().asSeconds();

    float beatNumber = currentTime / SECONDS_PER_BEAT;

    int closestBeat = static_cast<int>(beatNumber + 0.5f); 
    float expectedTime = closestBeat * SECONDS_PER_BEAT;

    if (Engine::GetInputManager()->IsKeyPressed(KEY_S))
    {
        float timeDifference = std::abs(currentTime - expectedTime);
        if (timeDifference <= TIMING_WINDOW)
        {
            CONSOLE_OUTPUT(L"gud" << std::endl);
        }
        else
        {
            CONSOLE_OUTPUT(L"Missed! (" << timeDifference << "s off)" << std::endl);
        }
    }
}

void PlayerMovement::OnDisable()
{
	music.stop();
}
