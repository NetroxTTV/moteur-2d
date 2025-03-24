#pragma once
#include <SFML/Graphics.hpp>

class KeyCounter {
public:
    KeyCounter(const std::string& keyLabel, sf::Vector2f position, sf::Font& font);

    void update(float deltaTime, bool isPressed);
    void draw(sf::RenderWindow& window);

    void increment();
    void reset();

private:
    sf::RectangleShape background;
    sf::Text keyText;
    sf::Text counterText;

    int count = 0;
    float alpha = 0.f;
    bool fadingIn = false;

    const float fadeSpeed = 300.f; 
    bool wasPressedLastFrame = false;
};
