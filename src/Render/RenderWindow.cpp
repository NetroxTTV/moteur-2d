#include "RenderWindow.h"

#include "Sprite.h"

RenderWindow::RenderWindow(std::string title, int width, int height, uint32_t style)
: sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), title, style)
{}

void RenderWindow::BeginFrame()
{
    clear(sf::Color::Black);
}

void RenderWindow::Draw(Sprite* sprite)
{
    draw(*sprite->GetSprite());
}

void RenderWindow::Draw(const sf::Text* text)
{
    draw(*text);
}

void RenderWindow::EndFrame()
{
    display();
}

int RenderWindow::GetWindowWidth()
{
    return static_cast<int>(getSize().x);
}

int RenderWindow::GetWindowHeight()
{
    return static_cast<int>(getSize().y);
}