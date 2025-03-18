#include "pch.h"
#include "Editor.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/ui/Image.h"
#include "scripts/PlayerMovement.h"
#include "scripts/tilemap/TilemapEditor.h"

void Editor::OnEnter()
{

    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    gridContainer->GetTransform()->SetPosition(0.0f, 0.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(gridContainer, Resources::instance().DEFAULT_SPRITE);

    ObjectFactory::AttachScript<TilemapEditor>(gridContainer);
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, -500.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    player->SetTag(Entity::Tag::PLAYER);
    
    ObjectFactory::AttachScript<PlayerMovement>(player);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>(player);
    ObjectFactory::CreateComponent<Camera>(camera);
    
}

void Editor::Render()
{
    
}
