#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
void RestartGame(SMode1& smode1, SMode2& smode2, SMode3& smode3, SMode4& smode4, Game& game)
{
	game.AppleEatSound.setBuffer(game.AppleEatbuffer);
	game.DeathSound.setBuffer(game.DeathSoundbuffer);

	game.AppleEatSound.setVolume(Volume);
	game.DeathSound.setVolume(Volume);

	InitPlayer(game.player, game);

	// mode1
	smode1.position = { SCREEN_WIDTH / 11.5f , SCREEN_HEIGHT / 2.f };
	smode1.Mode1Sprite.setTexture(game.Mode1Texture);
	setSpriteSize(smode1.Mode1Sprite, Mode_SIZE, Mode_SIZE);
	setSpriteOrigin(smode1.Mode1Sprite, 0.5f, 0.5f);

	// Imode2
	smode2.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 9.5f };
	smode2.Mode2Sprite.setTexture(game.Mode2Texture);
	setSpriteSize(smode2.Mode2Sprite, Mode_SIZE, Mode_SIZE);
	setSpriteOrigin(smode2.Mode2Sprite, 0.5f, 0.5f);

	// mode3
	smode3.position = { SCREEN_WIDTH - 70.5f , SCREEN_HEIGHT / 2.f };
	smode3.Mode3Sprite.setTexture(game.Mode3Texture);
	setSpriteSize(smode3.Mode3Sprite, Mode_SIZE, Mode_SIZE);
	setSpriteOrigin(smode3.Mode3Sprite, 0.5f, 0.5f);

	// mode4
	smode4.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 70.5f };
	smode4.Mode4Sprite.setTexture(game.Mode4Texture);
	setSpriteSize(smode4.Mode4Sprite, Mode_SIZE, Mode_SIZE);
	setSpriteOrigin(smode4.Mode4Sprite, 0.5f, 0.5f);


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
	int seed = (int)time(nullptr);
	srand(seed);

	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
	assert(game.AppleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
	assert(game.RockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
	assert(game.Mode1Texture.loadFromFile(RESOURCES_PATH + "\\Mode1.png"));
	assert(game.Mode2Texture.loadFromFile(RESOURCES_PATH + "\\Mode2.png"));
	assert(game.Mode3Texture.loadFromFile(RESOURCES_PATH + "\\Mode3.png"));
	assert(game.Mode4Texture.loadFromFile(RESOURCES_PATH + "\\Mode4.png"));

	if (!game.AppleEatbuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"))
	{

	}
	if (!game.DeathSoundbuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"))
	{

	}

	game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	game.background.setFillColor(sf::Color::Black);
	game.background.setPosition(0.f, 0.f);

	RestartGame(game.smode1, game.smode2, game.smode3, game.smode4, game);
}
 
void UpdateGame(Game& game, float deltaTime)
{
	if (game.isGame == true)
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

				RestartGame(game.smode1, game.smode2, game.smode3, game.smode4, game);
			}
		}
	}
	if (game.isGame == false)
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
		}
		for (int i = 0; i < 4; ++i)
		{
			// mode1
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.smode1.position, { Mode_SIZE, Mode_SIZE }))
			{
				game.isGameFinished = true;
				game.isGame = true;
				game.timeSinceGameFinish = 0.f;
				RestartGame(game.smode1, game.smode2, game.smode3, game.smode4, game);
				game.isGame = true;
				activeModes |= MODE_1;
			}
			// mode2
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.smode2.position, { Mode_SIZE, Mode_SIZE }))
			{
				game.isGameFinished = true;
				game.isGame = true;
				game.timeSinceGameFinish = 0.f;
				RestartGame(game.smode1, game.smode2, game.smode3, game.smode4, game);
				game.isGame = true;
				activeModes |= MODE_2;
			}
			// mode3
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.smode3.position, { Mode_SIZE, Mode_SIZE }))
			{
				game.isGameFinished = true;
				game.isGame = true;
				game.timeSinceGameFinish = 0.f;
				RestartGame(game.smode1, game.smode2, game.smode3, game.smode4, game);
				game.isGame = true;
				activeModes |= MODE_3;
			}
			// mode4
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.smode4.position, { Mode_SIZE, Mode_SIZE }))
			{
				game.isGameFinished = true;
				game.isGame = true;
				game.timeSinceGameFinish = 0.f;
				RestartGame(game.smode1, game.smode2, game.smode3, game.smode4, game);
				game.isGame = true;
				activeModes |= MODE_4;
			}
		}
		if (activeModes & MODE_1)
		{
			NUM_APPLES = (std::rand() % (50 - 1 + 1)) + 1;
		}
		if (activeModes & MODE_2)
		{
			NUM_APPLES = 20;
		}
		if (activeModes & MODE_3)
		{
			NUM_APPLES = 20;
			INITIAL_SPEED += PreSpeed;
			PreSpeed = 0;
		}
		if (activeModes & MODE_4)
		{
			NUM_APPLES = 50;
			INITIAL_SPEED += PreSpeed;
			PreSpeed = 0;
		}
	}
}

void DrawGame(SMode1& smode1, SMode2& smode2, SMode3& smode3, SMode4& smode4, Game& game, sf::RenderWindow& window)
{
	window.draw(game.background);
	DrawPlayer(game.player, window);
	if (game.isGame == true)
	{
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
	if (game.isGame == false)
	{
		//mode1
		smode1.Mode1Sprite.setPosition(smode1.position.x, smode1.position.y);
		window.draw(smode1.Mode1Sprite);
		//mode2
		smode2.Mode2Sprite.setPosition(smode2.position.x, smode2.position.y);
		window.draw(smode2.Mode2Sprite);
		//mode3
		smode3.Mode3Sprite.setPosition(smode3.position.x, smode3.position.y);
		window.draw(smode3.Mode3Sprite);
		//mode4
		smode4.Mode4Sprite.setPosition(smode4.position.x, smode4.position.y);
		window.draw(smode4.Mode4Sprite);
	}
}

void DeinializeGame(Game& game)
{

}