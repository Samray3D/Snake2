#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"


namespace Snake
{
	struct ScoreText
	{
		sf::Font font;
		sf::Text text;
	};

	struct Game;

	void InitScoreText(ScoreText& scoreText, const Game& game);
	void DrawScoreText(ScoreText& scoreText, sf::RenderWindow& window);
	void UpdateScoreText(ScoreText& scoreText, const std::string& message);
	void UpdateHighScoreDisplay(Game& game);
}
