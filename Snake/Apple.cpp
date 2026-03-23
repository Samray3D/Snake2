#include "Apple.h"
#include "Constants.h"
#include "Game.h"


namespace Snake
{

	void InitApple(Apple& apple, const Game& game)
	{
		apple.applePosition = GetRandomPositionInScreen(SCREEN_WIDTH - APPLE_SIZE / 2, SCREEN_HEIGHT - APPLE_SIZE / 2);
		
		apple.sprite.setTexture(game.appleTexture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		
		sf::FloatRect bounds = apple.sprite.getLocalBounds();
		apple.sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.applePosition.x, apple.applePosition.y);
		window.draw(apple.sprite);
	}
}
