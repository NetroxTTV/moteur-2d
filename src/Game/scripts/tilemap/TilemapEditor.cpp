#include "pch.h"

#include "TilemapEditor.h"
#include "Transform.h"

#include "Resources.h"
#include "SpriteSheet.h"
#include "ECS/Components/Camera.h"
#include "ECS/Systems/CameraSystem.h"

TilemapEditor::TilemapEditor() : mSelector({16, 16}), mTiles(), mOffset({0, 0}) { }

void TilemapEditor::OnStart()
{
    mTransform = owner->GetTransform();
    mGridVertices = sf::VertexArray(sf::PrimitiveType::Triangles);

    mOffset.x = halfMapSize;
    mOffset.y = halfMapSize;

    mSelector.setFillColor(sf::Color::Red);

    Sprite* sprite = new Sprite(*Resources::instance().SPRITE_SHEET);
    spriteSheet = new SpriteSheet(sprite);
    
    spriteSheet->Extract(0, 16, 16, 16, 480, 480);

    for (int x = 0; x <= tilePerRow; x++) {
        int tileX = x * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, mapSize), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, mapSize), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, mapSize), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, 0), sf::Color::White));

    }
    
    for (int y = 0; y <= tilePerRow; y++) {
        int tileY = y * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+2), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY+2), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+2), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));

    }
}

void TilemapEditor::OnFixedUpdate()
{
    if (movement.x > tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({tileSize+.0f, 0.0f}));
        movement = {0, 0};
    } else if (movement.x < -tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({-tileSize+.0f, 0.0f}));
        movement = {0, 0};
    } else if (movement.y > tileSize) {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({0.f, tileSize+.0f}));
        movement = {0, 0};
    } else if (movement.y < -tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({0.f, -tileSize+.0f}));
        movement = {0, 0};
    }
}

void TilemapEditor::OnUpdate()
{
    mCurrentCase.x = (mousePosition.x/tileSize) * tileSize + mTransform->position.x + 2;
    mCurrentCase.y= (mousePosition.y/tileSize) * tileSize + mTransform->position.y + 2;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        int index = tilePerRow * (mCurrentCase.y/tileSize-2) + (mCurrentCase.x/tileSize-2);
       if (!mUsedTile.contains(index))
       {
           mUsedTile.emplace(index);
           mTiles.push_back(Tile("", sf::Vector2f(mCurrentCase)));
       }
    }

    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        movement += mTransform->right * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        movement -= mTransform->right * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        movement += mTransform->up * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        movement -= mTransform->up * Engine::GetDeltaTime() * 1000.0f;
    }

    
    if (isKeyPressed(sf::Keyboard::Key::Subtract))
    {
        Engine::GetCameraSystem()->GetActiveCamera()->ZoomFactor += 1.0f * Engine::GetDeltaTime();
    }

    if (isKeyPressed(sf::Keyboard::Key::Add))
    {
        Engine::GetCameraSystem()->GetActiveCamera()->ZoomFactor -= 1.0f * Engine::GetDeltaTime();
    }
    
}

void TilemapEditor::OnRender(RenderWindow* window)
{
    
    mousePosition = sf::Mouse::getPosition(*window);
    mSelector.setPosition(sf::Vector2f(mCurrentCase));
    
    window->draw(mSelector);
    window->draw(mGridVertices);

    Debug::Log("Tile number " + std::to_string(mTiles.size()));
    int i = 0;
    for (Sprite* sprite : spriteSheet->GetSprites())
    {
        i++;
        sprite->setPosition({20.0f*i, 850.0f});
        window->Draw(sprite);
    }
    
}
