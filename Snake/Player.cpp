#include "Player.h"
#include "Game.h"
#include "Math.h"


namespace Snake
{

	void InitPlayer(Player& player)
	{

		player.playerPosition = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = PlayerDirection::Right;

	};

	const sf::Texture* GetBodyTextureForSegment(const Game& game, size_t index)
	{

		if (game.bodyPositions.empty() || index >= game.bodyPositions.size())
			return nullptr;

		if (index == game.bodyPositions.size() - 1)
		{
			if (index == 0)
				return nullptr;

			auto prev = game.bodyPositions[index - 1];
			auto curr = game.bodyPositions[index];

			float dx = curr.x - prev.x;
			float dy = curr.y - prev.y;

			if (dy < 0) return &game.tailUpTexture;
			if (dy > 0) return &game.tailDownTexture;
			if (dx < 0) return &game.tailLeftTexture;
			if (dx > 0) return &game.tailRightTexture;

			return &game.tailUpTexture;
		}
		if (index == 0) return nullptr;
		auto prev = game.bodyPositions[index - 1];
		auto curr = game.bodyPositions[index];
		auto next = game.bodyPositions[index + 1];

		float in_dx = curr.x - prev.x;
		float in_dy = curr.y - prev.y;
		float out_dx = next.x - curr.x;
		float out_dy = next.y - curr.y;

		if (in_dx == out_dx && in_dy == out_dy)
		{
			if (std::abs(in_dx) != 0) return &game.bodyHorizontalTexture;
			if (std::abs(in_dy) != 0) return &game.bodyVerticalTexture;
		}
		if ((in_dy < 0 && out_dx < 0) || (in_dx > 0 && out_dy > 0)) return &game.bodyBottomLeftTexture;
		if ((in_dy < 0 && out_dx > 0) || (in_dx < 0 && out_dy > 0)) return &game.bodyBottomRightTexture;
		if ((in_dy > 0 && out_dx < 0) || (in_dx > 0 && out_dy < 0)) return &game.bodyTopLeftTexture;
		if ((in_dy > 0 && out_dx > 0) || (in_dx < 0 && out_dy < 0)) return &game.bodyTopRightTexture;

		return &game.bodyHorizontalTexture;

	};

	void DrawSnakeBody(Game& game, sf::RenderWindow& window)
	{
		for (size_t i = 1; i < game.bodyPositions.size(); ++i)
		{
			if (i == 0) continue;
			sf::Sprite segmentSprite;
			const sf::Texture* chosenTexture = GetBodyTextureForSegment(game, i);
			if (chosenTexture && chosenTexture->getSize().x > 0)
			{
				segmentSprite.setTexture(*chosenTexture);
			}
			segmentSprite.setPosition(game.bodyPositions[i].x, game.bodyPositions[i].y);
			SetSpriteSize(segmentSprite, PLAYER_SIZE, PLAYER_SIZE);
			sf::FloatRect bounds = segmentSprite.getLocalBounds();
			segmentSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
			window.draw(segmentSprite);
		}
	};
	void UpdateSnakePixelPositions(Game& game)
	{
		if (game.bodyGridPositions.empty())
			return;

		game.bodyPositions.clear();

		for (const auto& gridPos : game.bodyGridPositions)
		{
			float pixelX = gridPos.x * game.gridSize + game.gridSize / 2.f;
			float pixelY = gridPos.y * game.gridSize + game.gridSize / 2.f;
			game.bodyPositions.push_back({ pixelX, pixelY });
		}
		if (!game.bodyPositions.empty())
		{
			const auto& headPos = game.bodyPositions.front();
			game.player.playerPosition.x = headPos.x;
			game.player.playerPosition.y = headPos.y;
			game.player.playerSprite.setPosition(game.player.playerPosition.x, game.player.playerPosition.y);
		}
	};
}
