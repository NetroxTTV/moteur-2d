#include "pch.h"
#include "GameScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/ui/Image.h"

#include "scripts/PlayerMovement.h"
#include "scripts/MusicScript.h"


void GameScene::OnEnter()
{

    srand(static_cast<unsigned int>(time(nullptr)));
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, 0.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    player->SetTag(Entity::Tag::PLAYER);
    
    MusicScript* music = ObjectFactory::AttachScript<MusicScript>(player);
    music->AddBeatmap(1, "../../res/Beatmaps/5.txt", "../../res/Music/5.mp3", 191.95f); // fingercontrol
    music->AddBeatmap(2, "../../res/Beatmaps/4.txt", "../../res/Music/4.ogg", 260.f); // high bpm
	music->AddBeatmap(3, "../../res/Beatmaps/3.txt", "../../res/Music/3.mp3", 129.25f); 
	music->AddBeatmap(4, "../../res/Beatmaps/6.txt", "../../res/Music/6.mp3", 230.f);

    ObjectFactory::AttachScript<PlayerMovement>(player);
    ObjectFactory::AttachScript<Inventory>(player);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);

    Entity* expBar = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Image>(expBar, Resources::instance().DEFAULT_SPRITE);

    
}

void GameScene::OnUpdate()
{

}