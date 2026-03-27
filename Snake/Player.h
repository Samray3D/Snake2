#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"


namespace Snake
{
	struct Game;


	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down,
	};

	struct Player
	{
		Position2D playerPosition;
		float playerSpeed = INITIAL_SPEED;
		PlayerDirection playerDirection = PlayerDirection::Right;
		sf::Sprite playerSprite;
	};

	void InitPlayer(Player& player);
	void DrawSnakeBody(Game& game, sf::RenderWindow& window);
	const sf::Texture* GetBodyTextureForSegment(const Game& game, size_t index);
	void UpdateSnakePixelPositions(Game& game);
}

