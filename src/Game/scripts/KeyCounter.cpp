#include "pch.h"
#include "KeyCounter.h"
#include <sstream>

KeyCounter::KeyCounter(const std::string& keyLabel, sf::Vector2f position, sf::Font& font) : 
	counterText(font), 
    keyText(font)
{
    background.setSize(sf::Vector2f(100, 60));
    background.setPosition(sf::Vector2f(position.x + 1300.f + 10.f, position.y));
    background.setFillColor(sf::Color(255, 255, 255, 0));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2.f);

    keyText.setFont(font);
    keyText.setCharacterSize(18);
    keyText.setFillColor(sf::Color::Black);
    keyText.setString(keyLabel);
    keyText.setPosition(sf::Vector2f(position.x + 1300.f + 30.f, position.y + 5.f));

    counterText.setFont(font);
    counterText.setCharacterSize(18);
    counterText.setFillColor(sf::Color::Black);
    counterText.setString("0");
    counterText.setPosition(sf::Vector2f(position.x + 1300.f + 30.f, position.y + 30.f));
}

void KeyCounter::update(float deltaTime, bool isPressed)
{
    if (isPressed && !wasPressedLastFrame)
    {
        fadingIn = true;
        alpha = 150;
        increment();
    }

    wasPressedLastFrame = isPressed;

    if (alpha > 0)
    {
        alpha -= fadeSpeed * deltaTime;
        if (alpha < 0) alpha = 0;
        background.setFillColor(sf::Color(128, 128, 128, alpha));
    }
    else
    {
        background.setFillColor(sf::Color(255, 255, 255, 0));
    }
}


void KeyCounter::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(keyText);
    window.draw(counterText);
}

void KeyCounter::increment()
{
   count++;
   counterText.setString(std::to_string(count));
   CONSOLE_OUTPUT(count << std::endl);
}

void KeyCounter::reset()
{
    count = 0;
    counterText.setString("0");
}
