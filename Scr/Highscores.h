#pragma once
#include <string>
#include <vector>


class Highscores
{
public:
	Highscores(std::string filename ="highscores.txt");
	~Highscores() = default;

	struct highscoreData {
		std::string playerWon; 
		int score;
	};

	std::vector<highscoreData> GetHighscores() const;
	void AddHighScore(highscoreData newScore);
private:
	std::string m_FileName{ };
};
