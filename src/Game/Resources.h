#pragma once

class Sprite;

class Resources
{
public:
    Resources() = default;
    ~Resources();
    
    void Initialize();
    void CreateShaders();
    void CreateParticles();
    void CreateTextures();
    void CreateSprite();
    void CreateFonts();
    
    static Resources& instance()
    {
        static Resources instance;
        return instance;
    }

    ////////////////////////////////
    /////// SHADERS

    //Shader* DEFAULT_SHADER;
    
    ////////////////////////////////
    /////// TEXTURES

    Texture* DEFAULT_TEXTURE;
    
    ////////////////////////////////
    /////// SPRITES

    Sprite* DEFAULT_SPRITE;

    ////////////////////////////////
    /////// FONTS

    sf::Font* DEFAULT_FONT;
};
