#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

using namespace sf;

struct Apple
{
	Position2D position;
	sf::Sprite applesprite;
};

struct Game;

void InitApple(Apple& apple, const Game& game);
void DrawApple(Apple& apple, sf::RenderWindow& window);
