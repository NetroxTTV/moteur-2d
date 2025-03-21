#include "pch.h"
#include "CameraSystem.h"

#include <iostream>

#include "ECS/ECS.h"
#include "ECS/Components/Camera.h"
#include "Render/RenderWindow.h"

CameraSystem::CameraSystem(RenderWindow* window)
: mCurrentDisplayedCamera(0), mCurrentCamera(nullptr),
                                                   mWindow(window)
{
}

void CameraSystem::SetActiveCamera(int activeCamera)
{
    mCurrentDisplayedCamera = activeCamera;
}

Camera* CameraSystem::GetActiveCamera()
{
    return mCurrentCamera;
}

void CameraSystem::Update(ECS* globalEC)
{
    bool foundCamera = false;
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (!globalEC->HasComponent<Camera>(i)) continue;
        Camera* camera = globalEC->GetComponent<Camera>(i);
        
        if (camera->DisplayScreen != mCurrentDisplayedCamera) continue;
        TRANSFORM* transform = camera->GetEntity()->GetTransform();
        sf::View view = sf::View(sf::FloatRect(transform->position, sf::Vector2f(1600, 900)));
        view.zoom(camera->ZoomFactor);
        mWindow->setView(view);
        mCurrentCamera = camera;
        foundCamera = true;
        break;
    }
    if (!foundCamera)
    {
        std::cout << "No camera found on " << mCurrentDisplayedCamera << std::endl;
    }
}
