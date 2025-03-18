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
    //
}

void PlayerMovement::OnFixedUpdate()
{
    //
}

void PlayerMovement::OnUpdate()
{
    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        movement += owner->GetTransform()->right * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        movement -= owner->GetTransform()->right * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        movement += owner->GetTransform()->up * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        movement -= owner->GetTransform()->up * Engine::GetDeltaTime();
    }
}

void PlayerMovement::OnDisable()
{
    //
}
