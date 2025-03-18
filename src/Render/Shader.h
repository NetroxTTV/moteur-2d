#pragma once
#include <SFML/Graphics/Shader.hpp>

class Shader : public sf::Shader
{
public:
    Shader(std::wstring path, sf::Shader::Type type);
    ~Shader() = default;
};
