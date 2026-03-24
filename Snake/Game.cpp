#include "Game.h"
#include <cassert>
#include "Apple.h"
#include "GameOver.h"
#include <string>
#include <iostream>
#include <deque>



namespace Snake
{
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
				if (std::abs(in_dx) > 0) return &game.bodyHorizontalTexture;
				if (std::abs(in_dy) > 0) return &game.bodyVerticalTexture;
			}
			if (in_dy < 0 &&  out_dx > 0) return &game.bodyBottomRightTexture;
			if (in_dy < 0 && out_dx < 0) return &game.bodyBottomLeftTexture;
			if (in_dy > 0 && out_dx > 0) return &game.bodyTopRightTexture;
			if (in_dy > 0 && out_dx < 0) return &game.bodyTopLeftTexture;

			if (in_dx > 0 && out_dy > 0) return &game.bodyBottomRightTexture;
			if (in_dx > 0 && out_dy < 0) return &game.bodyTopRightTexture;
			if (in_dx < 0 && out_dy > 0) return &game.bodyBottomLeftTexture;
			if (in_dx < 0 && out_dy < 0) return &game.bodyTopLeftTexture;

			return &game.bodyHorizontalTexture;

	}

	void DrawSnakeBody(Game& game, sf::RenderWindow& window)
	{
		for (size_t i = 0; i < game.bodyPositions.size(); ++i)
		{
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
	}

	void RestartGame(Game& game)
	{

		game.blsPaused = false;
		game.player.playerPosition.x = SCREEN_WIDTH / 2.f;
		game.player.playerPosition.y = SCREEN_HEIGHT / 2.f;
		game.player.playerDirection = PlayerDirection::Right;
		game.lastDirection = static_cast<int>(PlayerDirection::Right);

		game.player.playerSprite.setTexture(game.playerRightTexture);
		game.player.playerSprite.setPosition(game.player.playerPosition.x, game.player.playerPosition.y);

		game.bodyPositions.clear();

		Snake::Position2D headPos = game.player.playerPosition;

		game.bodyPositions.push_back({ headPos.x - PLAYER_SIZE, headPos.y });
		game.bodyPositions.push_back({ headPos.x - PLAYER_SIZE * 2, headPos.y });

		game.apple.applePosition = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		game.apple.sprite.setPosition(game.apple.applePosition.x, game.apple.applePosition.y);
		game.numAppleEaten = 0;
		
		UpdateScoreText(game.scoreText, "Score: 0");

		if (game.musicEnable && game.backgroundMusic.getStatus() != sf::Music::Playing)
		{
			game.backgroundMusic.play();
		}
		else if (!game.musicEnable)
		{
			game.backgroundMusic.pause();
		}
	}

	void InitGame(Game& game)
	{
		assert(game.playerRightTexture.loadFromFile(RESOURCES_PATH + "head_right.png"));
		assert(game.playerUpTexture.loadFromFile(RESOURCES_PATH + "head_up.png"));
		assert(game.playerLeftTexture.loadFromFile(RESOURCES_PATH + "head_left.png"));
		assert(game.playerDownTexture.loadFromFile(RESOURCES_PATH + "head_down.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "apple.png"));

		game.backgroundTexture.loadFromFile(RESOURCES_PATH + "background.png");
		game.backgroundSprite.setTexture(game.backgroundTexture);
		game.backgroundSprite.setScale(
			static_cast<float>(SCREEN_WIDTH) / game.backgroundTexture.getSize().x,
			static_cast<float>(SCREEN_HEIGHT) / game.backgroundTexture.getSize().y
		);

		if (!game.bodyHorizontalTexture.loadFromFile(RESOURCES_PATH + "body_horizontal.png"))
			std::cerr << "not loaded body_horizontal.png\n";
		if (!game.bodyVerticalTexture.loadFromFile(RESOURCES_PATH + "body_vertical.png"))
			std::cerr << "not loaded body_vertical.png\n";
		if (!game.tailUpTexture.loadFromFile(RESOURCES_PATH + "tail_up.png"))
			std::cerr << "not loaded tail_up.png\n";
		if (!game.tailDownTexture.loadFromFile(RESOURCES_PATH + "tail_down.png"))
			std::cerr << "not loaded tail_down.png\n";
		if (!game.tailLeftTexture.loadFromFile(RESOURCES_PATH + "tail_left.png"))
			std::cerr << "not loaded tail_left.png\n";
		if (!game.tailRightTexture.loadFromFile(RESOURCES_PATH + "tail_Right.png"))
			std::cerr << "not loaded tail_right.png\n";
		if (!game.bodyBottomLeftTexture.loadFromFile(RESOURCES_PATH + "body_bottomleft.png"))
			std::cerr << "not loaded body_bottomleft.png\n";
		if (!game.bodyBottomRightTexture.loadFromFile(RESOURCES_PATH + "body_bottomright.png"))
			std::cerr << "not loaded body_bottomright.png\n";
		if (!game.bodyTopLeftTexture.loadFromFile(RESOURCES_PATH + "body_topleft.png"))
			std::cerr << "not loaded body_topleft.png\n";
		if (!game.bodyTopRightTexture.loadFromFile(RESOURCES_PATH + "body_topright.png"))
			std::cerr << "not loaded body_topright.png\n";

		if (!game.font.loadFromFile(RESOURCES_PATH + "Fonts/Pixeboy.ttf"))
		{
			std::cerr << "Не удалось загрузить шрифт Pixeboy.ttf";
		}
		game.highScoreTitleText.setFont(game.font);
		game.highScoreTitleText.setString("HIGH SCORES");
		game.highScoreTitleText.setCharacterSize(60);
		game.highScoreTitleText.setFillColor(sf::Color::Yellow);
		game.highScoreTitleText.setStyle(sf::Text::Bold);
		sf::FloatRect titleBounds = game.highScoreTitleText.getLocalBounds();
		game.highScoreTitleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
		game.highScoreTitleText.setPosition(SCREEN_WIDTH / 2.f, 30.f);

		game.highScoreTexts.resize(10);
		for (size_t i = 0; i < game.highScoreTexts.size(); ++i)
		{
			game.highScoreTexts[i].setFont(game.font);
			game.highScoreTexts[i].setCharacterSize(38);
			game.highScoreTexts[i].setFillColor(sf::Color::White);
			game.highScoreTexts[i].setPosition(SCREEN_WIDTH / 2.f - 220.f, 120.f + i * 55.f);
		}



		assert(game.eatSoundBuffer.loadFromFile(RESOURCES_PATH + "eat.wav"));
		game.eatSound.setBuffer(game.eatSoundBuffer);

		assert(game.deathWallSoundBuffer.loadFromFile(RESOURCES_PATH + "deathWall.wav"));
		game.deathWallSound.setBuffer(game.deathWallSoundBuffer);

		InitScoreText(game.scoreText, game);

		assert(game.gameOverTexture.loadFromFile(RESOURCES_PATH + "gameOver.jpg"));
		InitGameOver(game.gameOver, game);

		InitPlayer(game.player);
		game.player.playerSprite.setTexture(game.playerRightTexture);
		SetSpriteSize(game.player.playerSprite, PLAYER_SIZE, PLAYER_SIZE);
		sf::FloatRect bounds = game.player.playerSprite.getLocalBounds();
		game.player.playerSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		game.player.playerSprite.setPosition(game.player.playerPosition.x, game.player.playerPosition.y);



		InitApple(game.apple, game);
		game.numAppleEaten = 0;

		game.blsPaused = false;
		game.pauseTime = 8.f;
		game.pauseTimeLeft = 0.f;

		RestartGame(game);

		game.titleText.setFont(game.font);
		game.titleText.setString("SNAKE");
		game.titleText.setCharacterSize(80);
		game.titleText.setFillColor(sf::Color(100, 255, 100));
		game.titleText.setStyle(sf::Text::Bold);
		sf::FloatRect titleB = game.titleText.getLocalBounds();
		game.titleText.setOrigin(titleB.width / 2.f, titleB.height / 2.f);
		game.titleText.setPosition(SCREEN_WIDTH / 2.f, 80.f);

		std::vector<std::string> menuString =
		{
			"Start game",
			"Difficulty",
			"Leaderboard",
			"Settings",
			"Exit"
		};

		game.menuItems.resize(menuString.size());
		float menuY = 200.f;
		float spacing = 60.f;

		for (size_t i = 0; i < menuString.size(); ++i)
		{
			game.menuItems[i].setFont(game.font);
			game.menuItems[i].setString(menuString[i]);
			game.menuItems[i].setCharacterSize(42);
			game.menuItems[i].setFillColor(sf::Color::White);

			sf::FloatRect bounds = game.menuItems[i].getLocalBounds();
			game.menuItems[i].setOrigin(bounds.width / 2.f, bounds.height / 2.f);
			game.menuItems[i].setPosition(SCREEN_WIDTH / 2.f, menuY + i * spacing);

		}

		game.state = GameState::Menu;
		game.selectedMenuItem = 0;

		std::vector<std::string> difficultyNames =
		{
			"Easy",
			"HarderThanEasy",
			"Medium",
			"EasierThanHard",
			"Hard"
		};
		game.difficultyItems.resize(difficultyNames.size());
		float diffY = 180.f;
		float diffSpacing = 70.f;

		for (size_t i = 0; i < difficultyNames.size(); ++i)
		{
			game.difficultyItems[i].setFont(game.font);
			game.difficultyItems[i].setString(difficultyNames[i]);
			game.difficultyItems[i].setCharacterSize(42);
			game.difficultyItems[i].setFillColor(sf::Color::White);

			sf::FloatRect bounds = game.difficultyItems[i].getLocalBounds();
			game.difficultyItems[i].setOrigin(bounds.width / 2.f, bounds.height / 2.f);
			game.difficultyItems[i].setPosition(SCREEN_WIDTH / 2.f, diffY + i * diffSpacing);
		}
		game.selectedDifficulty = 2;

		if (!game.backgroundMusic.openFromFile(RESOURCES_PATH + "background.ogg"))
		{
			std::cerr << "not loaded background.ogg\n";
		}
		else
		{
			game.backgroundMusic.setLoop(true);
			game.backgroundMusic.setVolume(25.f);
			game.musicEnable = true;
			game.soundEnable = true;
			if (game.musicEnable)
				game.backgroundMusic.play();
		}

	}


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

	void UpdateGame(Game& game, float deltaTime, sf::RenderWindow& window)
	{
		if (game.state == GameState::Menu)
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				&& !game.keyPressedLastFrame)
			{
				game.selectedMenuItem = (game.selectedMenuItem + 1) % static_cast<int>(game.menuItems.size());
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(120));
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				&& !game.keyPressedLastFrame)
			{
				game.selectedMenuItem = (game.selectedMenuItem - 1 + static_cast<int>(game.menuItems.size())) % static_cast<int>(game.menuItems.size());
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(120));
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				&& !game.keyPressedLastFrame)
			{
				switch (game.selectedMenuItem)
				{
				case 0: game.state = GameState::Playing;
					RestartGame(game);
					break;
				case 1: game.state = GameState::DifficultySelect;
					break;
				case 2: game.state = GameState::HighScores;
					UpdateHighScoreDisplay(game);
					break;
				case 3: game.state = GameState::Settings;
					break;
				case 4:
					window.close();
					break;
				}
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(200));
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game.keyPressedLastFrame = false;
			}
			return;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !game.keyPressedLastFrame)
		{
			game.state = GameState::Menu;
			game.selectedMenuItem = 0;
			game.keyPressedLastFrame = true;
			sf::sleep(sf::milliseconds(200));
			return;
		}

		if (game.state == GameState::DifficultySelect)
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				&& !game.keyPressedLastFrame)
			{
				game.selectedDifficulty = (game.selectedDifficulty + 1) % 5;
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(120));
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				&& !game.keyPressedLastFrame)
			{
				game.selectedDifficulty = (game.selectedDifficulty - 1 + 5) % 5;
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(120));
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				&& !game.keyPressedLastFrame)
			{
				game.difficultyLevel = game.selectedDifficulty;
				float speedMultiplier = 1.0f + game.difficultyLevel * 0.4f;
				game.player.playerSpeed = game.baseSpeed * speedMultiplier;

				int multipliers[5] = { 2, 4, 6, 8, 10 };
				game.scoreMultiplier = multipliers[game.difficultyLevel];

				game.state = GameState::Menu;
				game.selectedMenuItem = 0;
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(200));
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game.keyPressedLastFrame = false;
			}
			return;
		}

		if (game.state == GameState::Settings)
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				&& !game.keyPressedLastFrame)
			{
				game.selectedSettingsItem = (game.selectedSettingsItem + 1) % 2;
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(120));
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				&& !game.keyPressedLastFrame)
			{
				game.selectedSettingsItem = (game.selectedSettingsItem - 1 + 2) % 2;
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(120));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !game.keyPressedLastFrame)
			{
				if (game.selectedSettingsItem == 0)
				{
					game.soundEnable = !game.soundEnable;
				}
				else if (game.selectedSettingsItem == 1)
				{
					game.musicEnable = !game.musicEnable;

					if (game.musicEnable)
					{
						if (game.backgroundMusic.getStatus() != sf::Music::Playing)
							game.backgroundMusic.play();
					}
					else
					{
						game.backgroundMusic.pause();
					}
				}
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(150));

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !game.keyPressedLastFrame)
			{
				game.state = GameState::Menu;
				game.selectedMenuItem = 3;
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(150));
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game.keyPressedLastFrame = false;
			}
			return;

		}
		if (game.state == GameState::Playing && !game.blsPaused)
		{

			bool ateAppleThisFrame = false;

			Position2D oldHeadPosition = game.player.playerPosition;

			int newDirection = static_cast<int>(game.player.playerDirection);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				newDirection = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				newDirection = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				newDirection = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				newDirection = 3;
			}

			if ((newDirection + 2) % 4 != game.lastDirection)
			{
				game.player.playerDirection = static_cast<PlayerDirection>(newDirection);
				switch (game.player.playerDirection)
				{
				case PlayerDirection::Right: game.player.playerSprite.setTexture(game.playerRightTexture); break;
				case PlayerDirection::Up: game.player.playerSprite.setTexture(game.playerUpTexture); break;
				case PlayerDirection::Left: game.player.playerSprite.setTexture(game.playerLeftTexture); break;
				case PlayerDirection::Down: game.player.playerSprite.setTexture(game.playerDownTexture); break;
				}
			}

			game.lastDirection = static_cast<int>(game.player.playerDirection);

			switch (game.player.playerDirection)
			{

			case PlayerDirection::Right: game.player.playerPosition.x += game.player.playerSpeed * deltaTime;
				break;

			case PlayerDirection::Up: game.player.playerPosition.y -= game.player.playerSpeed * deltaTime;
				break;

			case PlayerDirection::Left:	game.player.playerPosition.x -= game.player.playerSpeed * deltaTime;
				break;

			case PlayerDirection::Down:	game.player.playerPosition.y += game.player.playerSpeed * deltaTime;
				break;


			}

			if (isCirclesCollide(game.player.playerPosition, PLAYER_SIZE / 2.f,
				game.apple.applePosition, APPLE_SIZE / 2.f))
			{
				game.apple.applePosition = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				++game.numAppleEaten;
				game.numAppleEaten += game.scoreMultiplier;
				UpdateScoreText(game.scoreText, "Score: " + std::to_string(game.numAppleEaten));
				game.apple.sprite.setPosition(game.apple.applePosition.x, game.apple.applePosition.y);
				if (game.soundEnable)
					game.eatSound.play();

				ateAppleThisFrame = true;

			}

			game.bodyPositions.push_front(game.player.playerPosition);

			if (!ateAppleThisFrame && !game.bodyPositions.empty())
			{
				game.bodyPositions.pop_back();
			}

			for (const auto& pos : game.bodyPositions)
			{
				if (pos.x - PLAYER_SIZE / 2.f < 0.f ||
					pos.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
					pos.y - PLAYER_SIZE / 2.f < 0.f ||
					pos.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
				{
					game.blsPaused = true;
					game.pauseTimeLeft = 9999.f;
					if (game.soundEnable)
						game.deathWallSound.play();

					bool added = game.highScoreManager.TryAddScore(game.numAppleEaten);
					game.isNewHighScore = added;

					game.state = GameState::GameOver;

					game.gameOver.fadeClock.restart();
					game.gameOver.sprite.setColor(sf::Color(255, 255, 255, 0));

					UpdateHighScoreDisplay(game);
					break;
				}
			}
		}
		if (game.state == GameState::GameOver || game.state == GameState::HighScores)
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				&& !game.keyPressedLastFrame)
			{
				game.state = GameState::Playing;
				game.isNewHighScore = false;
				RestartGame(game);
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(200));
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				&& !game.keyPressedLastFrame)
			{
				game.state = GameState::Menu;
				game.selectedMenuItem = 0;
				game.keyPressedLastFrame = true;
				sf::sleep(sf::milliseconds(200));
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game.keyPressedLastFrame = false;
			}
		}
	}
	

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		window.clear();
		window.draw(game.backgroundSprite);

		if (game.state == GameState::Menu)
		{
			window.draw(game.backgroundSprite);
			window.draw(game.titleText);

			for (size_t i = 0; i < game.menuItems.size(); ++i)
			{
				sf::Text& item = game.menuItems[i];
				if (static_cast<int>(i) == game.selectedMenuItem)
				{
					item.setFillColor(sf::Color(100, 255, 100));
					item.setStyle(sf::Text::Bold);
					item.setCharacterSize(48);
				}
				else
				{
					item.setFillColor(sf::Color::White);
					item.setStyle(sf::Text::Regular);
					item.setCharacterSize(42);
				}
				window.draw(item);
			}

		}

		else if (game.state == GameState::Settings)
		{
			window.clear();
			window.draw(game.backgroundSprite);
			sf::Text title("SETTINGS", game.font, 60);
			title.setFillColor(sf::Color::Yellow);
			title.setStyle(sf::Text::Bold);
			title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);
			title.setPosition(SCREEN_WIDTH / 2.f, 80.f);
			window.draw(title);
			if (game.settingsItems.empty())
			{
				std::vector<std::string> names = { "Sound", "Music" };
				game.settingsItems.resize(2);
				float y = 200.f;
				for (size_t i = 0; i < 2; ++i)
				{
					game.settingsItems[i].setFont(game.font);
					game.settingsItems[i].setString(names[i]);
					game.settingsItems[i].setCharacterSize(42);
					game.settingsItems[i].setFillColor(sf::Color::White);
					game.settingsItems[i].setOrigin(game.settingsItems[i].getLocalBounds().width / 2.f, game.settingsItems[i].getLocalBounds().height / 2.f);
					game.settingsItems[i].setPosition(SCREEN_WIDTH / 2.f - 80.f, y + i * 80.f);
				}
			}
			for (size_t i = 0; i < game.settingsItems.size(); ++i)
			{
				auto& item = game.settingsItems[i];
				bool selected = (static_cast<int>(i) == game.selectedSettingsItem);
				bool enabled = (i == 0 ? game.soundEnable : game.musicEnable);

				item.setFillColor(selected ? sf::Color(100, 255, 100) : sf::Color::White);
				item.setStyle(selected ? sf::Text::Bold : sf::Text::Regular);
				item.setCharacterSize(selected ? 48 : 42);
				window.draw(item);

				float cbX = SCREEN_WIDTH / 2.f + 140.f;
				float cbY = item.getPosition().y - 20.f;

				sf::RectangleShape box({ 40.f, 40.f });
				box.setPosition(cbX, cbY);
				box.setFillColor(sf::Color::Transparent);
				box.setOutlineColor(sf::Color::White);
				box.setOutlineThickness(3.f);
				window.draw(box);

				if (enabled)
				{
					sf::Text check("+", game.font, 42);
					check.setFillColor(sf::Color(100, 255, 100));
					check.setPosition(cbX + 5.f, cbY - 5.f);
					window.draw(check);
				}
			}

		}

		else if (game.state == GameState::DifficultySelect)
		{
			window.clear();
			window.draw(game.backgroundSprite);
			sf::Text title;
			title.setFont(game.font);
			title.setString("DIFFICULTY");
			title.setCharacterSize(60);
			title.setFillColor(sf::Color::Yellow);
			title.setStyle(sf::Text::Bold);
			sf::FloatRect tb = title.getLocalBounds();
			title.setOrigin(tb.width / 2.f, tb.height / 2.f);
			title.setPosition(SCREEN_WIDTH / 2.f, 80.f);
			window.draw(title);

			for (size_t i = 0; i < game.difficultyItems.size(); ++i)
			{
				sf::Text& item = game.difficultyItems[i];
				if (static_cast<int>(i) == game.selectedDifficulty)
				{
					item.setFillColor(sf::Color(100, 255, 100));
					item.setStyle(sf::Text::Regular);
					item.setCharacterSize(48);
				}
				else
				{
					item.setFillColor(sf::Color::White);
					item.setStyle(sf::Text::Regular);
					item.setCharacterSize(42);
				}
				window.draw(item);
			}

		}
		else if (game.state == GameState::Playing)
		{
			DrawScoreText(game.scoreText, window);
			DrawApple(game.apple, window);
			DrawSnakeBody(game, window);
			game.player.playerSprite.setPosition(game.player.playerPosition.x, game.player.playerPosition.y);
			window.draw(game.player.playerSprite);
		}
		else if (game.state == GameState::GameOver)
		{
			DrawScoreText(game.scoreText, window);
			DrawSnakeBody(game, window);
			window.draw(game.player.playerSprite);
			DrawGameOver(game.gameOver, window);
			if (game.isNewHighScore)
			{
				sf::Text congrats;
				congrats.setFont(game.font);
				congrats.setString("NEW HIGH SCORE!");
				congrats.setCharacterSize(52);
				congrats.setFillColor(sf::Color::Red);
				congrats.setStyle(sf::Text::Bold);
				sf::FloatRect b = congrats.getLocalBounds();
				congrats.setOrigin(b.width / 2.f, b.height / 2.f);
				congrats.setPosition(SCREEN_WIDTH / 2.f, 80.f);
				window.draw(congrats);
			}
			sf::Text pressText;
			pressText.setFont(game.font);
			pressText.setString("press SPACE or ENTER to restart or ESC to back in Main menu");
			pressText.setCharacterSize(32);
			pressText.setFillColor(sf::Color(200, 200, 255));
			pressText.setStyle(sf::Text::Bold);
			sf::FloatRect pb = pressText.getLocalBounds();
			pressText.setOrigin(pb.width / 2.f, pb.height / 2.f);
			pressText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 80.f);
			window.draw(pressText);
		}
		
		if (game.state == GameState::GameOver || game.state == GameState::HighScores)
		{
			window.draw(game.highScoreTitleText);
			for (const auto& txt : game.highScoreTexts)
			{
				if (!txt.getString().isEmpty())
					window.draw(txt);
			}
		}
		
	
		window.display();


	}
}
