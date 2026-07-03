#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void ModeSwith(Game& game)
{
	if (Mode == 0)
	{
		NUM_APPLES = (std::rand() % (50 - 1 + 1)) + 1;
	}
	if (Mode == 1)
	{
		NUM_APPLES = 20;
	}
	if (Mode == 2)
	{
		NUM_APPLES = 20;
		INITIAL_SPEED += 70.f;
	}
	if (Mode == 3)
	{
		NUM_APPLES = 50;
		INITIAL_SPEED += 70.f;
	}
	if (Mode > 3)
	{
		INITIAL_SPEED += 9000.f;
	}
	if (Mode < 0)
	{
		INITIAL_SPEED += 9000.f;
	}
}

void RestartGame(Game& game)
{
	game.AppleEatSound.setBuffer(game.AppleEatbuffer);
	game.DeathSound.setBuffer(game.DeathSoundbuffer);

	game.AppleEatSound.setVolume(Volume);
	game.DeathSound.setVolume(Volume);

	InitPlayer(game.player, game);

	// Init apples
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		InitApple(game.apples[i], game);
	}

	// Init rocks
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		InitRock(game.rocks[i], game);
	}

	game.numEatenApples = 0;
	game.isGameFinished = false;
	game.timeSinceGameFinish = 0;
}

void InitGame(Game& game)
{
	ModeSwith(game);
	int seed = (int)time(nullptr);
	srand(seed);

	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
	assert(game.AppleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
	assert(game.RockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

	if (!game.AppleEatbuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"))
	{

	}
	if (!game.DeathSoundbuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"))
	{

	}

	game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	game.background.setFillColor(sf::Color::Black);
	game.background.setPosition(0.f, 0.f);

	RestartGame(game);
}

void UpdateGame(Game& game, float deltaTime)
{
	// Update game state
	if (!game.isGameFinished)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			game.player.direction = PlayerDirection::Right;
			playerRight(game.player);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			game.player.direction = PlayerDirection::Up;
			playerUp(game.player);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			game.player.direction = PlayerDirection::Left;
			playerLeft(game.player);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			game.player.direction = PlayerDirection::Down;
			playerDown(game.player);
		}

		// Update player state
		switch (game.player.direction)
		{
		case PlayerDirection::Right:
		{
			game.player.position.x += game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			game.player.position.y -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			game.player.position.x -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			game.player.position.y += game.player.speed * deltaTime;
			break;
		}
		}

		// Find player collisions with apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
				game.apples[i].position, APPLE_SIZE / 2.f))
			{
				game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				++game.numEatenApples;
				game.player.speed += ACCELERATION;
				game.AppleEatSound.play();
			}
		}

		// Find player collisions with rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
			{
				game.isGameFinished = true;
				game.timeSinceGameFinish = 0.f;
				game.DeathSound.play();
			}
		}

		// Check screen borders collision
		if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			game.isGameFinished = true;
			game.timeSinceGameFinish = 0.f;
			game.DeathSound.play();
		}
	}
	else
	{
		if (game.timeSinceGameFinish <= PAUSE_LENGTH)
		{
			game.timeSinceGameFinish += deltaTime;
			game.background.setFillColor(sf::Color::Red);
		}
		else
		{
			// Reset backgound
			game.background.setFillColor(sf::Color::Black);

			RestartGame(game);
		}
	}
}

void DrawGame(Game& game, sf::RenderWindow& window)
{
	window.draw(game.background);
	DrawPlayer(game.player, window);
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		//ModeSwith(game);
		DrawApple(game.apples[i], window);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		DrawRock(game.rocks[i], window);
	}

}

void DeinializeGame(Game& game)
{

}