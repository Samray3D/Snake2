#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"

int main()
{	
	using namespace Snake;
	int seed = (int)time(nullptr);
	srand(seed);

	Game game;
	InitGame(game);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();
	
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake");

	while (window.isOpen())
	{
		
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		//{
		//	window.close();
		//}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		UpdateGame(game, deltaTime, window);
		DrawGame(game, window);
		
		}


	return 0;
}
