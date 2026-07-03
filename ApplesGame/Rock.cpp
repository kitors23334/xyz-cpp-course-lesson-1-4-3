#include "Rock.h"
#include "Game.h"

void InitRock(Rock& rock, const Game& game)
{
	rock.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	rock.rocksprite.setTexture(game.RockTexture);
	setSpriteSize(rock.rocksprite, ROCK_SIZE, ROCK_SIZE);
	setSpriteOrigin(rock.rocksprite, 0.5f, 0.5f);
}

void DrawRock(Rock& rock, sf::RenderWindow& window)
{
	rock.rocksprite.setPosition(rock.position.x, rock.position.y);
	window.draw(rock.rocksprite);
}