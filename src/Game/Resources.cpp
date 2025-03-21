#include "pch.h"
#include "Resources.h"

#include "Render/Sprite.h"
#include "Render/Texture.h"

Resources::~Resources()
{
}

void Resources::Initialize()
{
    Resources* resources = &instance();
    
    resources->CreateShaders();
    resources->CreateParticles();
    resources->CreateTextures();
    resources->CreateSprite();
    resources->CreateFonts();
}

void Resources::CreateShaders()
{
    //DEFAULT_SHADER = new Shader("shaderPath", Shader::Type::Vertex);
}

void Resources::CreateParticles()
{
}

void Resources::CreateTextures()
{
    DEFAULT_TEXTURE = new Texture("perso.png");
    SPRITE_SHEET = new Texture("../../res/Tiles/tileset.png", false);
}

void Resources::CreateSprite()
{
    DEFAULT_SPRITE = new Sprite(*DEFAULT_TEXTURE);
}

void Resources::CreateFonts()
{
    DEFAULT_FONT = new sf::Font("../../res/Fonts/arial.ttf");
}
