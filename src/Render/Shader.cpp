#include "Shader.h"

Shader::Shader(std::wstring name, sf::Shader::Type type) : sf::Shader(L"../../res/Shaders/" + name, type) { }
