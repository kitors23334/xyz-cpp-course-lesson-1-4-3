#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include <vector>

struct Game
{
	Player player;
	Apple apples[Const_NUM_APPLES];
	Rock rocks[NUM_ROCKS];

	// Global game data
	int count = 0;
	int Precount = 0;
	int numEatenApples = 0;
	bool isGameFinished = false;
	float timeSinceGameFinish = 0.f;
	sf::RectangleShape background;

	//Resources
	sf::Texture playerTexture;
	sf::Texture AppleTexture;
	sf::Texture RockTexture;
	sf::Sound DeathSound;
	sf::Sound AppleEatSound;
	sf::SoundBuffer AppleEatbuffer;
	sf::SoundBuffer DeathSoundbuffer;
};

void RestartGame(Game& game);
void InitGame(Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(Game& game, sf::RenderWindow& window);
void DeinializeGame(Game& game);
void ModeSwith(Game& game);