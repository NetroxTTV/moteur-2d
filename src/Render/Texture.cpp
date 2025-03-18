#include "Texture.h"

#include "Engine/Utils/Debug.h"

Texture::Texture(std::string name)
{
    if (loadFromFile("../../res/Textures/" + name))
    {
        Debug::Error("La texture " + name + " was not found.");
    }
}
