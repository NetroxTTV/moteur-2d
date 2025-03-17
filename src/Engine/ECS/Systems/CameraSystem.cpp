#include "pch.h"
#include "CameraSystem.h"

#include <iostream>

#include "ECS/ECS.h"
#include "ECS/Components/Camera.h"
#include "Render/RenderWindow.h"

CameraSystem::CameraSystem(RenderWindow* window) : mCurrentDisplayedCamera(0), mWindow(window){ }

void CameraSystem::SetActiveCamera(int activeCamera)
{
    mCurrentDisplayedCamera = activeCamera;
}

void CameraSystem::Update(ECS* globalEC)
{
    bool foundCamera = false;
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (!globalEC->HasComponent<Camera>(i)) continue;
        Camera* camera = globalEC->GetComponent<Camera>(i);
        TRANSFORM* transform = camera->GetEntity()->GetTransform();
        
        sf::View view = sf::View(sf::FloatRect(transform->position, sf::Vector2f(1600, 900)));
        mWindow->setView(view);
        foundCamera = true;
        break;
    }
    if (!foundCamera)
    {
        std::cout << "No camera found on " << mCurrentDisplayedCamera << std::endl;
    }
}
