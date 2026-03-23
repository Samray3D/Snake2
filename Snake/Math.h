#pragma once

namespace sf
{
	class Sprite;
}

namespace Snake
{

	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};

	typedef Vector2D Position2D;


	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

	bool isCirclesCollide(Position2D circle1Position, float circle1Radius,
		Position2D circle2Position, float circle2Radius);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
}