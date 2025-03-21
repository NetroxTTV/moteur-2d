#pragma once

#include "scripts/Script.h"
#include <set>

class SpriteSheet;

struct Tile
{
    std::string tileName;
    sf::Vector2f position;
};

class TilemapEditor : public IScript
{

    std::string mPAthToTileSet = "../../res/Tiles/tileset.png";

    int currentTileIndex = 0;
    std::vector<Tile> tileMap;
    SpriteSheet* spriteSheet ;

    std::vector<Tile> mTiles;
    std::set<int> mUsedTile;
    
    TRANSFORM* mTransform;
    sf::Vector2f movement;
    
    sf::Vector2i mousePosition;
    
    sf::RectangleShape mSelector;
    sf::VertexArray mGridVertices;

    sf::Vector2i mCurrentCase;
    sf::Vector2i mOffset;

    int mapSize = 5000;
    int halfMapSize = mapSize/2;
    int tileSize = 16;
    int tilePerRow = mapSize/tileSize;
    int totalTile = tilePerRow*tilePerRow;

public:
    TilemapEditor();
    void OnStart() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
    void OnRender(RenderWindow* window) override;
};
