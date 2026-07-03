#include "Player.h"
#include "Game.h"

void InitPlayer(Player& player, const Game& game)
{
	// Init player state
	player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
	player.speed = INITIAL_SPEED;
	player.direction = PlayerDirection::Right;

	// init player sprite
	player.sprite.setTexture(game.playerTexture);
	setSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
	setSpriteOrigin(player.sprite, 0.5f, 0.5f);
}

void DrawPlayer(Player& player, sf::RenderWindow& window)
{
	player.sprite.setPosition(player.position.x, player.position.y);
	window.draw(player.sprite);
}

//вращение
void playerRight(Player& player)
{
	player.sprite.setRotation(360.f);
}
void playerUp(Player& player)
{
	player.sprite.setRotation(-90.f);
}
void playerLeft(Player& player)
{
	player.sprite.setRotation(-180.f);
}
void playerDown(Player& player)
{
	player.sprite.setRotation(90.f);
}