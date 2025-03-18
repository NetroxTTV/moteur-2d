#include "pch.h"
#include "MusicScript.h"

void MusicScript::OnStart()
{
    //if (!music.openFromFile("../../res/Music/musique.mp3"))
    //{
    //    std::cerr << "Error loading musique.mp3" << std::endl;
    //    return;
    //}

    //music.play();
    beatClock.restart();

    hitRect.setFillColor(sf::Color::White);
	hitRect.setSize(sf::Vector2f(100.f, 1.f));
    hitRect.setPosition(sf::Vector2(0.f, 700.f));

}

void MusicScript::OnFixedUpdate()
{
}

void MusicScript::OnUpdate()
{
    float currentTime = beatClock.getElapsedTime().asSeconds();

    float beatNumber = currentTime / SECONDS_PER_BEAT;
    int closestBeat = static_cast<int>(beatNumber + 0.5f);
    float expectedTime = closestBeat * SECONDS_PER_BEAT;

    static sf::Clock frameClock;
    float deltaTime = frameClock.restart().asSeconds();

    if (static_cast<int>(beatNumber) > static_cast<int>((currentTime - deltaTime) / SECONDS_PER_BEAT))
    {
        sf::CircleShape circle(30.f);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(sf::Vector2(400.f, 0.f));
        fallingCircles.push_back(circle);
    }

    for (auto& circle : fallingCircles)
    {
        circle.move(sf::Vector2f(0.f, FALL_SPEED * deltaTime));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
    {
        float timeDifference = std::abs(currentTime - expectedTime);
        if (timeDifference <= TIMING_WINDOW)
        {
            CONSOLE_OUTPUT(L"Perfect hit!" << std::endl);
        }
        else
        {
            CONSOLE_OUTPUT(L"Missed! (" << timeDifference << "s off)" << std::endl);
        }
    }

    Render();
}

void MusicScript::OnDisable()
{
    //music.stop();
}

void MusicScript::Render()
{
	Engine::GetRenderWindow()->draw(hitRect);

    for (const auto& circle : fallingCircles)
    {
        Engine::GetRenderWindow()->draw(circle);
    }
}