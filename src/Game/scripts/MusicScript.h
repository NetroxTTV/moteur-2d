#pragma once
#include "scripts/Script.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics/Text.hpp>

#include <map>

class RigidBody2D;

class MusicScript : public IScript
{
	enum class MUSICSTATE
	{
		PLAYING,
		PAUSED,
		STOPPED
	};

    struct BeatCircle
    {
        sf::CircleShape shape;
        float spawnTime;
    };

    struct NoteData
    {
        int x;
        int y;
        float time;
    };

    struct BeatMapData {
        const char* beatmapFile;
        const char* musicFile;
		float bpm;
	};;

public:
    MusicScript();

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

    void OnRender(RenderWindow* window) override;
    void LoadNotesFromFile(const char* filename);
    void PlayBeatmap(int key);
    void SetState(MUSICSTATE state) { mState = state; }
    MUSICSTATE GetState() { return mState; }

	void IncreaseCombo();
	void ResetCombo();
    void ShowCombo(sf::RenderWindow& window);
    void Missed();

	void SetupTexts();
    void SetHitAreas();

    void AddBeatmap(int key, const const char* beatmapFile, const char* musicFile, float bpm) { musicList.emplace(key, new BeatMapData(beatmapFile, musicFile, bpm) ); }

private:
    float BPM = 1.f;
    float SECONDS_PER_BEAT = 60.0f / BPM;
    const float TIMING_WINDOW = 0.15f;
    const float FALL_SPEED = 100.0f;
	const float AR = 8.0f;
    bool musicStarted;
    bool sKeyPressed = false;
    bool dKeyPressed = false;
    float firstNote;
    int noteCounter = 0;
	int Misses = 0;

    sf::Vector2f movement;
    sf::Clock beatClock;
	sf::Music music;
    std::vector<BeatCircle> fallingCircles;
    std::vector<NoteData> noteDataList;
    sf::RectangleShape hitRect;
	sf::CircleShape hitCircle;
    sf::RenderWindow* window = nullptr;

    sf::Text comboText;
    sf::Text maxComboText; 
	sf::Text BPMText;
    sf::Text MissCount;

    int combo = 0;
    int maxCombo = 0;

	MUSICSTATE mState;
	std::map<int, BeatMapData*> musicList;
};