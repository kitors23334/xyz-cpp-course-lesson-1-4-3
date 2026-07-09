#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "ModeSwith.h"
#include "LeaderBoard.h"

struct Game
{
	SMode1 smode1;
	SMode2 smode2;
	SMode3 smode3;
	SMode4 smode4;

	SMode5 smode5;
	SMode6 smode6;
	SMode7 smode7;
	SMode8 smode8;
	sf::Font font;

	Player player;
	//Apple apples[Const_NUM_APPLES];
	Apple* apples = new Apple[NUM_APPLES];
	Rock rocks[NUM_ROCKS];


	// Global game data
	int count = 0;
	int Precount = 0;
	int numEatenApples = 0;
	bool isGameFinished = false;
	bool isGame = false;
	bool StopSpawn = false;
	float timeSinceGameFinish = 0.f;
	sf::RectangleShape background;

	//Resources
	sf::Texture playerTexture;
	sf::Texture AppleTexture;
	sf::Texture RockTexture;

	sf::Texture Mode1Texture;
	sf::Texture Mode2Texture;
	sf::Texture Mode3Texture;
	sf::Texture Mode4Texture;

	sf::Texture Mode5Texture;
	sf::Texture Mode6Texture;
	sf::Texture Mode7Texture;
	sf::Texture Mode8Texture;

	sf::Sound DeathSound;
	sf::Sound AppleEatSound;
	sf::SoundBuffer AppleEatbuffer;
	sf::SoundBuffer DeathSoundbuffer;
};

void RestartGame(SMode1& smode1, SMode2& smode2, SMode3& smode3, SMode4& smode4, SMode5& smode5, SMode6& smode6, SMode7& smode7, SMode8& smode8, Game& game);
void InitGame(Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(SMode1& smode1, SMode2& smode2, SMode3& smode3, SMode4& smode4, SMode5& smode5, SMode6& smode6, SMode7& smode7, SMode8& smode8, Game& game, sf::RenderWindow& window);
void DeinializeGame(Game& game);