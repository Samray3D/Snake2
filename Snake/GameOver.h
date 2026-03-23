#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"


namespace Snake
{
	struct GameOver
	{
		Position2D position;
		sf::Sprite sprite;
		
		sf::Clock fadeClock;
		bool fadeActive = false;
		
	};

	struct Game;

	void InitGameOver(GameOver& gameOver, const Game& game);
	void DrawGameOver(GameOver& gameOver, sf::RenderWindow& window);
}