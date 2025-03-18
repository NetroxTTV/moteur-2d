#include "Sprite.h"

#include "Texture.h"

Sprite::Sprite(Texture& texture) : sf::Sprite(texture)
{
}

Sprite::Sprite(sf::Sprite& sprite) : sf::Sprite(sprite)
{
    return;
}

void Sprite::SetAlpha(uint8_t alpha)
{
    sf::Color color = getColor();
    color.a = alpha;
    setColor(color);
}

Sprite* Sprite::Cut(int x, int y, int width, int height)
{
    sf::Sprite part = sf::Sprite(static_cast<sf::Sprite>(*this));
    part.setTextureRect(sf::IntRect({x,y}, {width,height}));
    part.scale({1.0f, 1.0f});
    return new Sprite(part);
}