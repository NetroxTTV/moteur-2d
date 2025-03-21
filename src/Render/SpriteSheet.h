#pragma once

#include <map>
#include <SFML/Graphics/Texture.hpp>

class Sprite;

class SpriteSheet
{
    std::vector<Sprite*> sprites;

public:
    Sprite* spriteSheet;
    SpriteSheet(Sprite* sprite);
    void Extract(int startX, int startY, int singleWidth, int singleHeight, int width = 1, int height = 1);
    Sprite* GetSprite(int index);
    std::vector<Sprite*> GetSprites() const;
};
