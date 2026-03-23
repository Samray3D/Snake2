#include "Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <iostream>

const std::string HighScoreManager::HIGHSCORE_FILE = "highscores.txt";

HighScoreManager::HighScoreManager()
{
	Load();
}

void HighScoreManager::Load()
{
	scores.clear();
	std::ifstream file(HIGHSCORE_FILE);
	if (!file.is_open())
		return;
	std::string name;
	int score;
	while (file >> name >> score)
	{
		if (!name.empty() && score >= 0)
		{
			scores.push_back({ name, score });
		}
		file.close();

		std::sort(scores.begin(), scores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b)
			{
				return a.score > b.score;
			});
		if (scores.size() > MAX_SCORES)
		{
			scores.resize(MAX_SCORES);
		}
	}
}
void HighScoreManager::Save() const
{
	std::ofstream file(HIGHSCORE_FILE);
	if (!file.is_open())
	{
		std::cerr << "Не удалось открыть файл для записи рекордов\n";
		return;
	}
	for (const auto& entry : scores)
	{
		file << entry.name << " " << entry.score << "\n";
	}
	file.close();
}
bool HighScoreManager::TryAddScore(int score, const std::string& playerName)
{
	if (scores.size() < MAX_SCORES)
	{
		scores.push_back({ playerName, score });
		std::sort(scores.begin(), scores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b) {return a.score > b.score; });
		Save();
		return true;
	}
	if (score > scores.back().score)
	{
		scores.pop_back();
		scores.push_back({ playerName, score });
		std::sort(scores.begin(), scores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b) {return a.score > b.score; });
		Save();
		return true;
	}
	return false;
}
bool HighScoreManager::IsNewHighScore(int score) const
{
	if (scores.empty())
		return true;
	return score > scores.front().score;
}

const std::vector<HighScoreEntry>& HighScoreManager::GetTopScore() const
{
	return scores;
}