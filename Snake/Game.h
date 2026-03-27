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
		sf::Sprite playerSprite;
		sf::Vector2f playerPosition;
		
		Player player;
		Apple apple;

		GameState state = GameState::Playing;

		sf::Clock gameClock;
		float lastTime;
		float moveAccumulator;

		bool isNewHighScore = false;
		HighScoreManager highScoreManager;

		sf::Font font;
		sf::Text highScoreTitleText;
		std::vector<sf::Text> highScoreTexts;

		int selectedMenuItem = 0;
		std::vector<sf::Text> menuItems;
		sf::Text titleText;

		int difficultyLevel = 2;
		float baseSpeed = INITIAL_SPEED;
		int scoreMultiplier = 6;

		std::vector<sf::Text> difficultyItems;
		int selectedDifficulty = 2;

		int numAppleEaten = 0;

		bool blsPaused = false;
		float pauseTime = 3.f;
		float pauseTimeLeft = 0.f;
		int lastDirection = 0;

		bool soundEnable = true;
		bool musicEnable = true;

		sf::Music backgroundMusic;

		std::vector<sf::Text> settingsItems;
		int selectedSettingsItem = 0;
		bool keyPressedLastFrame = false;

		bool isPaused = false;
		bool isResumeDelayActive = false;
		float resumeDelayTime = 3.0f;
		float resumeDelayLeft = 0.0f;

		sf::Text pauseTitleText;
		sf::Text pauseContinueText;
		sf::Text pauseExitText;
		int selectedPauseItem = 0;
		bool justSwitchedState = false;

		bool isInvincible = false;
		float invincibleTimeLeft = 0.0f;
		bool skipCollisionFrame = false;

		float gridSize = PLAYER_SIZE;
		float moveInterval = 0.15f;
		float moveTimer = 0.0f;

		std::deque<sf::Vector2i> bodyGridPositions;
		PlayerDirection nextDirection;

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

		sf::SoundBuffer menuClickSoundBuffer;
		sf::Sound menuClickSound;
		

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