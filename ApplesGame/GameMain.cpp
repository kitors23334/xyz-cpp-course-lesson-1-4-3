// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"

struct PlayerScore 
{
	std::string name;
	int score;
};

void sortLeaderboard(std::vector<PlayerScore>& board) 
{

	size_t n = board.size();
	for (size_t i = 0; i < n - 1; ++i) {
		bool swapped = false;
		for (size_t j = 0; j < n - i - 1; ++j) {
			if (board[j].score < board[j + 1].score) { // по убыванию
				std::swap(board[j], board[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break; // оптимизация: если перестановок не было — массив уже отсортирован
	}
}
int main()
{
	Game game;

	int seed = static_cast<int>(time(nullptr));
	srand(seed);

	int Alice = (std::rand() % (200 - 1 + 1)) + 1;
	int Bob = (std::rand() % (200 - 1 + 1)) + 1;
	int Carol = (std::rand() % (200 - 1 + 1)) + 1;
	int Dave = (std::rand() % (200 - 1 + 1)) + 1;
	int Eve = (std::rand() % (200 - 1 + 1)) + 1;

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	InitGame(game);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
		// Calculate time delta
		std::vector<PlayerScore> leaderboard =
		{
			{"You",  game.numEatenApples},
			{"Alice",  Alice},
			{"Bob",     Bob},
			{"Carol",   Carol},
			{"Dave",    Dave},
			{"Eve",     Eve}
		};

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
				delete[] game.apples;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
				delete[] game.apples;
			}
		}

		UpdateGame(game, deltaTime);

		// Draw game
		window.clear();
		DrawGame(game.smode1, game.smode2, game.smode3, game.smode4, game.smode5, game.smode6, game.smode7, game.smode8, game, window);

		if (game.isGameFinished == true)
		{
			sortLeaderboard(leaderboard);

			// Заголовок
			sf::Text title("===== LEADERBOARD =====", game.font, 24);
			title.setFillColor(sf::Color::Green);
			title.setPosition(50, 50);
			window.draw(title);

			float y = 90;
			const float lineHeight = 30.0f;
			const int maxLineLen = 28;

			for (size_t i = 0; i < leaderboard.size(); ++i) {
				std::string line = std::to_string(i + 1) + ". " + leaderboard[i].name;
				int dotsNeeded = maxLineLen - static_cast<int>(line.length());
				if (dotsNeeded < 1) dotsNeeded = 1;

				std::string dots(dotsNeeded, '.');
				std::string fullLine = line + dots + std::to_string(leaderboard[i].score);

				sf::Text text(fullLine, game.font, 20);
				text.setFillColor(sf::Color::Green);
				text.setPosition(50, y);
				window.draw(text);

				y += lineHeight;
			}

			sf::Text footer("=======================", game.font, 24);
			footer.setFillColor(sf::Color::Green);
			footer.setPosition(50, y + 10);
			window.draw(footer);

		}

		window.display();
	}
	// Deinitialization
	DeinializeGame(game);

	return 0;
}