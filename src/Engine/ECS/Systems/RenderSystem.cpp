#include "pch.h"
#include "RenderSystem.h"

#include "Transform.h"
#include "ECS/ECS.h"
#include "../Components/SpriteRenderer.h"
#include "Render/RenderWindow.h"

RenderSystem::RenderSystem(RenderWindow* window): window(window) {}

void RenderSystem::Render(ECS* globalEC)
{
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (globalEC->HasComponent<SpriteRenderer>(i))
        {
            SpriteRenderer* renderer = globalEC->GetComponent<SpriteRenderer>(i);
            TRANSFORM* transform = renderer->GetEntity()->GetTransform();
            renderer->Image->setPosition(transform->position);
            renderer->Image->setScale(transform->scale);
            if (!renderer->RendererShader)
                window->Draw(renderer->Image);
            else
                window->Draw(renderer->Image, renderer->RendererShader);
        } else if (globalEC->HasComponent<Image>(i))
        {
            Image* image = globalEC->GetComponent<Image>(i);
            image->UIImage->setPosition(cameraTransform->position);
            window->Draw(image->UIImage);
        }
    }
}