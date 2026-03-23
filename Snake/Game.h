#pragma once
#include <SFML/Graphics.hpp>
#include "Apple.h"
#include "Player.h"
#include <SFML/Audio.hpp>
#include "GameOver.h"
#include "Score.h"
#include <deque>
#include "Leaderboard.h"


namespace Snake
{
	enum class GameState
	{
		Menu,
		Playing,
		GameOver,
		HighScores,
		DifficultySelect,
		Settings
	};

	struct Game
	{
		Player player;
		Apple apple;

		GameState state = GameState::Playing;

		bool isNewHighScore = false;
		HighScoreManager highScoreManager;

		sf::Font font;
		sf::Text highScoreTitleText;
		std::vector<sf::Text> highScoreTexts;

		int selectedMenuItem = 0;
		std::vector<sf::Text> menuItems;
		sf::Text titleText;


		int numAppleEaten = 0;

		bool blsPaused = false;
		float pauseTime = 3.f;
		float pauseTimeLeft = 0.f;
		int lastDirection = 0;

		sf::Texture appleTexture;
		sf::Texture playerRightTexture;
		sf::Texture playerUpTexture;
		sf::Texture playerLeftTexture;
		sf::Texture playerDownTexture;
		sf::Texture bodyHorizontalTexture;
		sf::Texture bodyVerticalTexture;
		sf::Texture bodyTopLeftTexture;
		sf::Texture bodyTopRightTexture;
		sf::Texture bodyBottomLeftTexture;
		sf::Texture bodyBottomRightTexture;
		sf::Texture tailUpTexture;
		sf::Texture tailDownTexture;
		sf::Texture tailLeftTexture;
		sf::Texture tailRightTexture;
		sf::Texture gameOverTexture;
		GameOver gameOver;
		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;

		sf::SoundBuffer eatSoundBuffer;
		sf::Sound eatSound;

		sf::SoundBuffer deathWallSoundBuffer;
		sf::Sound deathWallSound;
		sf::SoundBuffer deathTailSoundBuffer;
		sf::Sound deathTailSound;

		sf::Font scoreFont;
		ScoreText scoreText;

		std::deque<Snake::Position2D> bodyPositions;
		
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime, sf::RenderWindow& window);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DrawSnakeBody(Game& game, sf::RenderWindow& window);
	const sf::Texture* GetBodyTextureForSegment(const Game& game, size_t index);
}