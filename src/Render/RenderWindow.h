#pragma once

#include <SFML/Graphics.hpp>

#include "Sprite.h"

class RenderWindow final : public sf::RenderWindow
{
public:
    RenderWindow(std::string title, int width, int height, uint32_t style = sf::Style::Default);

    void BeginFrame();
    void Draw(Sprite* sprite);
    void Draw(const sf::Text* text);
    void EndFrame();
    
    int GetWindowWidth();
    int GetWindowHeight();
};