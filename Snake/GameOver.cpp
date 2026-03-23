#include "GameOver.h"
#include "Game.h"

namespace Snake
{
	void InitGameOver(GameOver& gameOver, const Game& game)
	{
		
		gameOver.sprite.setTexture(game.gameOverTexture);
		
		sf::FloatRect bounds = gameOver.sprite.getLocalBounds();
		gameOver.sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		gameOver.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		gameOver.fadeClock.restart();
		gameOver.fadeActive = false;
		gameOver.sprite.setColor(sf::Color(255, 255, 255, 0));



	};

	void DrawGameOver(GameOver& gameOver, sf::RenderWindow& window)
	{
		
		float elapsed = gameOver.fadeClock.getElapsedTime().asSeconds();
		fadeDuration;

		float progress = std::min(elapsed / fadeDuration, 1.f);
		sf::Uint8 alpha = static_cast<sf::Uint8>(progress * 255.f);
		gameOver.sprite.setColor(sf::Color(255, 255, 255, alpha));


		gameOver.sprite.setPosition(gameOver.position.x, gameOver.position.y);
		window.draw(gameOver.sprite);
	}
}

