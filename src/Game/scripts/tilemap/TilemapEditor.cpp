#include "pch.h"
#include "TilemapEditor.h"

void TilemapEditor::OnStart()
{
    gridVertices = sf::VertexArray(sf::PrimitiveType::Triangles);
    
    for (int x = 0; x <= 500; x += 10) {
        for (int y = 0; y <= 500; y += 10) {
            gridVertices.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::White));
            gridVertices.append(sf::Vertex(sf::Vector2f(x+50, y), sf::Color::White));
            gridVertices.append(sf::Vertex(sf::Vector2f(x+50, y+5), sf::Color::White));
            
            gridVertices.append(sf::Vertex(sf::Vector2f(x, y+5), sf::Color::White));
            gridVertices.append(sf::Vertex(sf::Vector2f(x+50, y+5), sf::Color::White));
            gridVertices.append(sf::Vertex(sf::Vector2f(x+50, y), sf::Color::White));

        }
    }
}

void TilemapEditor::OnUpdate()
{
    
}

void TilemapEditor::OnRender(RenderWindow* window)
{
    window->draw(gridVertices);
}
