#include "pch.h"
#include "MusicScript.h"
#include <fstream>
#include <sstream>

MusicScript::MusicScript() :
    comboText(*Resources::instance().DEFAULT_FONT), 
    maxComboText(*Resources::instance().DEFAULT_FONT), 
    BPMText(*Resources::instance().DEFAULT_FONT), 
    MissCount(*Resources::instance().DEFAULT_FONT)
{}


void MusicScript::SetupTexts()
{
	comboText.setCharacterSize(30);
	comboText.setFillColor(sf::Color::White);
	comboText.setPosition(sf::Vector2f(50, 50));
	maxComboText.setCharacterSize(30);
	maxComboText.setFillColor(sf::Color::White);
	maxComboText.setPosition(sf::Vector2f(50, 125));
	BPMText.setString("BPM: " + std::to_string(BPM));
	BPMText.setCharacterSize(30);
	BPMText.setFillColor(sf::Color::White);
	BPMText.setPosition(sf::Vector2f(50, 200));
    MissCount.setCharacterSize(30);
    MissCount.setFillColor(sf::Color::Red);
    MissCount.setPosition(sf::Vector2f(50, 275));
}

void MusicScript::SetHitAreas()
{
    hitRect.setFillColor(sf::Color::White);
    hitRect.setSize(sf::Vector2f(1920.f, 5.f));
    hitRect.setPosition(sf::Vector2(0.f, 810.f));

    hitCircle.setFillColor(sf::Color::Magenta);
    hitCircle.setRadius(50.f);
    hitCircle.setPosition(sf::Vector2(1550.f / 2 - 35.f, 760.f));
}

void MusicScript::OnStart()
{
    PlayBeatmap(2);
	SetupTexts();
	SetHitAreas();

    musicStarted = false;
    beatClock.restart();

    CONSOLE_OUTPUT(firstNote << std::endl);
}

void MusicScript::LoadNotesFromFile(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        CONSOLE_OUTPUT(L"Failed to open file: " << filename << std::endl);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string temp;
        int x, y;
        float time;

        std::getline(ss, temp, ','); x = std::stof(temp);
        std::getline(ss, temp, ','); y = std::stof(temp);
        std::getline(ss, temp, ','); time = std::stof(temp) / 1000.0f;

        noteDataList.push_back({ x, y, time });
    }
    firstNote = noteDataList[0].time;

    CONSOLE_OUTPUT(L"Loaded " << noteDataList.size() << L" notes from " << filename << std::endl);
}

void MusicScript::PlayBeatmap(int key)
{
    if (!music.openFromFile(musicList[key]->musicFile))
    {
        CONSOLE_OUTPUT(L"Error loading music" << std::endl);
        return;
    }

	LoadNotesFromFile(musicList[key]->beatmapFile);
    BPM = musicList[key]->bpm;

	SetState(MusicScript::MUSICSTATE::PLAYING);
}

void MusicScript::OnFixedUpdate()
{
}

void MusicScript::OnUpdate()
{
    if (mState == MusicScript::MUSICSTATE::PLAYING) {
        float currentTime = beatClock.getElapsedTime().asSeconds();
        float miniOffset = 20.f;

        if (!musicStarted)
        {
            float songOffset = ((hitRect.getPosition().y + miniOffset) / (FALL_SPEED * AR));

            if (currentTime + (noteDataList[0].time / 32) >= songOffset)
            {
                music.play();
                CONSOLE_OUTPUT(currentTime << std::endl);
                musicStarted = true;
            }
        }

        float beatNumber = currentTime / SECONDS_PER_BEAT;
        int closestBeat = static_cast<int>(beatNumber + 0.5f);
        float expectedTime = closestBeat * SECONDS_PER_BEAT;

        float realFallSpeed = FALL_SPEED * AR;

        static sf::Clock frameClock;
        float deltaTime = frameClock.restart().asSeconds();

        int noteCounter = 0;

        while (!noteDataList.empty() && noteDataList.front().time <= currentTime)
        {
            NoteData note = noteDataList.front();
            noteDataList.erase(noteDataList.begin());

            BeatCircle newCircle;
            newCircle.shape = sf::CircleShape(22.f);

            switch ((noteCounter / 5) % 5)
            {
            case 0: newCircle.shape.setFillColor(sf::Color::White); break;
            case 1: newCircle.shape.setFillColor(sf::Color::Red); break;
            case 2: newCircle.shape.setFillColor(sf::Color::Green); break;
            case 3: newCircle.shape.setFillColor(sf::Color::Blue); break;
            case 4: newCircle.shape.setFillColor(sf::Color::Yellow); break;
            }

            newCircle.shape.setPosition(sf::Vector2f(1540.f / 2, 0.f));
            newCircle.spawnTime = note.time;

            fallingCircles.push_back(newCircle);
            noteCounter++;
        }


        for (auto& beatCircle : fallingCircles)
        {
            beatCircle.shape.move(sf::Vector2f(0.f, FALL_SPEED * AR * deltaTime));

            float circleY = beatCircle.shape.getPosition().y;

            if (circleY > 850)
            {
                fallingCircles.erase(fallingCircles.begin());
                Missed();
                ResetCombo();
                break;
            }
        }

        bool sKeyNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
        bool dKeyNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

        if ((sKeyNow && !sKeyPressed) || (dKeyNow && !dKeyPressed))
        {
            sKeyPressed = sKeyNow;
            dKeyPressed = dKeyNow;

            for (auto it = fallingCircles.begin(); it != fallingCircles.end();)
            {
                sf::CircleShape& circle = it->shape;
                float spawnTime = it->spawnTime;

                float circleY = circle.getPosition().y;
                float hitY = hitRect.getPosition().y;

                float realFallSpeed = FALL_SPEED * AR;
                float hitExpectedTime = spawnTime + (hitY / realFallSpeed);

                if (std::abs(circleY - hitY) <= 180.0f)
                {
                    float timeDifference = std::abs(currentTime - hitExpectedTime);
                    if (timeDifference <= TIMING_WINDOW)
                    {
                        CONSOLE_OUTPUT(L"Perfect hit!" << std::endl);
                        IncreaseCombo();
                    }
                    else
                    {
                        CONSOLE_OUTPUT(L"Missed! (" << timeDifference << "s off)" << std::endl);
                        Missed();
                        ResetCombo();
                    }
                    it = fallingCircles.erase(it);
                    break;
                }
                else
                {
                    if (circleY > 900)
                    {
                        CONSOLE_OUTPUT(L"Missed!" << std::endl);
                        Missed();
                        ResetCombo();
                        it = fallingCircles.erase(it);
                    }
                    else
                    {
                        it++;
                    }
                }
            }
        }

        if (!sKeyNow) sKeyPressed = false;
        if (!dKeyNow) dKeyPressed = false;
    }
    else {
		mState = MusicScript::MUSICSTATE::STOPPED;
        return;
    }
}

void MusicScript::OnDisable()
{
    music.stop();
}

void MusicScript::OnRender(RenderWindow* window)
{
    window->draw(hitRect);
	window->draw(hitCircle);
	window->draw(BPMText);
	window->draw(MissCount);

    for (const auto& beatCircle : fallingCircles)
    {
        window->draw(beatCircle.shape);
    }
    ShowCombo(*window);
}

void MusicScript::ShowCombo(sf::RenderWindow& window) {
    comboText.setString("Combo: " + std::to_string(combo));
    maxComboText.setString("Max Combo: " + std::to_string(maxCombo));
    MissCount.setString("Miss : " + std::to_string(Misses));

    window.draw(comboText);
    window.draw(maxComboText);
}

void MusicScript::IncreaseCombo() {
    combo++;
    if (combo > maxCombo) {
        maxCombo = combo;
    }
}

void MusicScript::ResetCombo() {
    combo = 0;
}

void MusicScript::Missed() {
    Misses++;
}