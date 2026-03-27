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
	};

	void UpdateHighScoreDisplay(Game& game)
	{
		const auto& scores = game.highScoreManager.GetTopScore();
		for (size_t i = 0; i < game.highScoreTexts.size(); ++i)
		{
			if (i < scores.size())
			{
				std::string line = std::to_string(i + 1) + ". " + scores[i].name + " " + std::to_string(scores[i].score);
				game.highScoreTexts[i].setString(line);
				if (game.isNewHighScore && i == 0)
				{
					game.highScoreTexts[i].setFillColor(sf::Color::Yellow);
					game.highScoreTexts[i].setStyle(sf::Text::Bold);
				}
				else
				{
					game.highScoreTexts[i].setFillColor(sf::Color::White);
					game.highScoreTexts[i].setStyle(sf::Text::Regular);
				}
			}
			else
			{
				game.highScoreTexts[i].setString("");
			}
		}
	}
}
