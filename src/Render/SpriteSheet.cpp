#include "SpriteSheet.h"

#include "Sprite.h"
#include "Engine/Utils/Debug.h"

SpriteSheet::SpriteSheet(Sprite* spriteSheet): spriteSheet(spriteSheet)
{
}

void SpriteSheet::Extract(int startX, int startY, int singleWidth, int singleHeight, int width, int height)
{

    if (!spriteSheet)
    {
        Debug::Log("Sprite sheet can't be extract file not found or not load.");
    }

    for (int x = startX; x < startX+width; x+=singleWidth)
    {
        for (int y = startY; y < startY+height; y+=singleHeight)
        {

            sprites.push_back(spriteSheet->Cut(x, y, singleWidth, singleHeight));
            
        }
    }
    
}

Sprite* SpriteSheet::GetSprite(int index)
{
    return sprites[index];
}

std::vector<Sprite*> SpriteSheet::GetSprites() const
{
    return sprites;
}
