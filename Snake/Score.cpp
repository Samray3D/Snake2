#include "Score.h"
#include "Game.h"
#include <cassert>


namespace Snake
{
	void InitScoreText(ScoreText& scoreText, const Game& game)
	{
		assert(scoreText.font.loadFromFile(FONTS_PATH + "Roboto-BoldItalic.ttf"));

		scoreText.text.setFont(scoreText.font);
		scoreText.text.setCharacterSize(24);
		scoreText.text.setFillColor(sf::Color::Green);
		scoreText.text.setPosition(10.f, 10.f);
	};

	void DrawScoreText(ScoreText& scoreText, sf::RenderWindow& window)
	{
		window.draw(scoreText.text);
	};

	void UpdateScoreText(ScoreText& scoreText, const std::string& message)
	{
		scoreText.text.setString(message);
	}
}
