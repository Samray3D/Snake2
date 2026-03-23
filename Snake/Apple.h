#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"


namespace Snake
{

	struct Apple
	{
		Position2D applePosition;
		sf::Sprite sprite;

	};

	struct Game;

	void InitApple(Apple& apple, const Game& game);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}