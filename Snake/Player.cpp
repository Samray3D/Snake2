#include "Player.h"


namespace Snake
{

	void InitPlayer(Player& player)
	{

		player.playerPosition = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = PlayerDirection::Right;

		
	}
}
