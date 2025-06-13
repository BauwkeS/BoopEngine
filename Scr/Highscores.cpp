#include "Highscores.h"
#include <fstream>
#include <algorithm>

Highscores::Highscores(std::string filename) : m_FileName(std::move(filename))
{
}

std::vector<Highscores::highscoreData> Highscores::GetHighscores() const
{
	std::vector<Highscores::highscoreData> highscores;

	std::ifstream highscoreFile("Data\\" + m_FileName);

	if (!highscoreFile.is_open()) throw std::runtime_error("Failed to open game file: " + m_FileName);


	std::string line;
	while (std::getline(highscoreFile, line))
	{
		if (!line.empty())
		{
			//seperate the line into player name and score with ,
			size_t commaPos = line.find(',');
			if (commaPos != std::string::npos)
			{
				std::string playerName = line.substr(0, commaPos);
				int score = std::stoi(line.substr(commaPos + 1));
				highscores.push_back({ playerName, score });
			}
			else
			{
				throw std::runtime_error("Invalid highscore format in line: " + line);
			}


			//highscores.push_back(line);
		}
	}


	return highscores;
}

void Highscores::AddHighScore(highscoreData newScore)
{
	std::vector<Highscores::highscoreData> highscores = GetHighscores();

	//check if the score is higher than the lowest score in the highscores
	if (highscores.size() < 9 || newScore.score > highscores.back().score)
	{
		//add the new score
		highscores.push_back(newScore);
		//sort the highscores by score
		std::sort(highscores.begin(), highscores.end(), [](const highscoreData& a, const highscoreData& b) {
			return a.score > b.score;
			});
		//keep only the top 10 scores
		if (highscores.size() > 10) {
			highscores.resize(10);
		}
		//write the highscores to the file
		std::ofstream highscoreFile("Data\\" + m_FileName);
		if (!highscoreFile.is_open()) throw std::runtime_error("Failed to open game file: " + m_FileName);
		for (const auto& score : highscores)
		{
			highscoreFile << score.playerWon << "," << score.score << "\n";
		}
	}
}
