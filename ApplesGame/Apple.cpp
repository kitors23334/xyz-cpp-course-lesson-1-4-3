#include "Apple.h"
#include "Game.h"

using namespace sf;

void InitApple(Apple& apple, const Game& game)
{
	apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	apple.applesprite.setTexture(game.AppleTexture);
	setSpriteSize(apple.applesprite, APPLE_SIZE, APPLE_SIZE);
	setSpriteOrigin(apple.applesprite, 0.5f, 0.5f);
}

void DrawApple(Apple& apple, sf::RenderWindow& window)
{
	apple.applesprite.setPosition(apple.position.x, apple.position.y);
	window.draw(apple.applesprite);
}
