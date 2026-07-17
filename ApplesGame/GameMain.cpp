// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"
#include <vector>

struct PlayerScore 
{
	std::string name;
	int score;
};

const std::vector<std::wstring> options = {
	L"← Continue Game",
	L"← Main Menu",
	L"← = choose, ↑ = up, ↓ = down"
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
	int selectedIndex = 0;
	const float itemHeight = 50.f;
	const float startY = 200.f;

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

	sf::Clock pauseCooldown;      // таймер
	const float pauseDelay = 1.0f; // задержка
	sf::Clock pauseCooldownf;      // таймер
	const float pauseDelayf = 0.2f; // задержка

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
			if (game.isGame == false)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					break;
					delete[] game.apples;
				}
			}
		}

		UpdateGame(game, deltaTime);

		// Draw game
		window.clear();
		DrawGame(game.smode1, game.smode2, game.smode3, game.smode4, game.smode5, game.smode6, game.smode7, game.smode8, game, window);

		// TextR
		sf::Text TextR("A-left, W-forward, S-backward, D-right, esc-exit/menu, tab-leaderboard", game.font, 15);
		TextR.setFillColor(sf::Color::Green);
		TextR.setPosition(SCREEN_WIDTH - 490.5f, SCREEN_HEIGHT - 600.5f);
		window.draw(TextR);

		if (game.isGamepause == true)
		{
			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
				{
					if (pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
					{
						selectedIndex--;
						if (selectedIndex < 0) selectedIndex = static_cast<int>(options.size()) - 1;
						pauseCooldownf.restart();             // сбрасываем таймер
					}
				}
				else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
				{
					if (pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
					{
						selectedIndex++;
						if (selectedIndex >= static_cast<int>(options.size())) selectedIndex = 0;
						pauseCooldownf.restart();             // сбрасываем таймер
					}
				}
				else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Left) {
					// Тут вызываем нужную логику в зависимости от выбора
					if (selectedIndex == 0) {
						// Продолжить игру: просто выходим из меню
						game.isGamepause = false;
					}
					else if (selectedIndex == 1) {
						game.isGame = false;
						game.isGamepause = false;
						// Главное меню: здесь можно сбросить состояние игры, перейти в другой экран и т.п.
						// Например, вернуть какой-то флаг, что нужно показать главное меню
					}
				}
			}
			for (size_t i = 0; i < options.size(); ++i) {
				sf::Text text(options[i], game.font, 36);
				text.setFillColor(sf::Color::White);

				float y = startY + i * itemHeight;
				// Центрируем текст по горизонтали
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
				text.setPosition(window.getSize().x / 2.f, y);

				// Подсветка выбранного пункта
				if (static_cast<int>(i) == selectedIndex) {
					text.setFillColor(sf::Color::Yellow);
					// Можно ещё добавить обводку или рамку, если хочется
				}

				window.draw(text);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (pauseCooldown.getElapsedTime().asSeconds() >= pauseDelay)
			{
				game.isGamepause = (game.isGamepause ? false : true);
				pauseCooldown.restart();             // сбрасываем таймер
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
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