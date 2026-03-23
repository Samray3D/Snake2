#include "Math.h"
#include <cstdlib>
#include "Constants.h"
#include "SFML/Graphics.hpp"


namespace Snake 
{

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = APPLE_SIZE / 2.f + (rand() / (float)RAND_MAX) * (screenWidth - APPLE_SIZE);
		result.y = APPLE_SIZE / 2.f + (rand() / (float)RAND_MAX) * (screenHeight - APPLE_SIZE);
		return result;
	}

	bool isCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
	{
		float squareDistance = (circle1Position.x - circle2Position.x) * (circle1Position.x - circle2Position.x) + (circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
		float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
		return squareDistance <= squareRadiusSum;
	}
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredHeight / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
}
