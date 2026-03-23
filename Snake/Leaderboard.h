#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

struct HighScoreEntry
{
	std::string name;
	int score;
};

class HighScoreManager
{
public:
	HighScoreManager();
	void Load();
	void Save() const;
	bool TryAddScore(int score, const std::string& playerName = "Player");
	const std::vector<HighScoreEntry>& GetTopScore() const;
	bool IsNewHighScore(int score) const;
private:
	std::vector<HighScoreEntry> scores;
	static const size_t MAX_SCORES = 10;
	static const std::string HIGHSCORE_FILE;
};
