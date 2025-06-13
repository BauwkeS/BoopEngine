#include "LevelObserver.h"
#include "../../BoopEngine/Boop/GameObject.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../GameCommands.h"
#include "../GameLoader.h"

LevelObserver::LevelObserver()
	: m_Highscores{ std::make_unique<Highscores>() }
{
}

void LevelObserver::OnNotify(boop::Event event)
{
	//GO TO END SCREEN
	if (event.id == boop::make_sdbm_hash("PlayerDied"))
	{
		SetUpEndScreen();

		auto changeScene = booble::ChangeScene("EndingScreen");
		changeScene.Execute();
	}


	//GO TO NEXT LEVEL
	if (event.id == boop::make_sdbm_hash("PlayerKillTank")
		|| event.id == boop::make_sdbm_hash("PlayerKillRecognizer"))
	{
		//check if there are no more players on the scene
		auto scene = boop::SceneManager::GetInstance().GetActiveScene();
		auto enemyInfo = scene->FindAllGameObjectByTag("enemy");

		int enemiesLeft = static_cast<int>(enemyInfo.size());
		
		for (auto& enemy : enemyInfo)
		{
			if (!enemy->IsGhost()) return;
			//no more enemies, cleared the level
			--enemiesLeft;
			
		}
		if (enemiesLeft <= 0)
		{
			auto goToNextLevel = booble::SkipLevel();
			goToNextLevel.Execute();
		}
	}
}

void LevelObserver::SetUpEndScreen()
{
	//SETUP
	const std::string levelName{ "EndingScreen" };
	auto& endingScene = boop::SceneManager::GetInstance().AddScene(levelName);

	Highscores::highscoreData endData = GetEndData();
	m_Highscores->AddHighScore(endData);

	//selection info
	auto mainTexts = std::make_unique<boop::GameObject>();
	mainTexts->AddComponent<boop::TextComponent>("GAME OVER: " + endData.playerWon + " won!")->SetPosition(300, 100);
	mainTexts->AddComponent<boop::TextComponent>("With score: " + std::to_string(endData.score))->SetPosition(300, 200);

	endingScene.Add(std::move(mainTexts));


	auto getScores = m_Highscores->GetHighscores();

	auto scoretext = std::make_unique<boop::GameObject>();
	scoretext->AddComponent<boop::TextComponent>("Scores::")->SetPosition(300, 240);

	for (int i = 0; i < getScores.size(); i++)
	{
		scoretext->AddComponent<boop::TextComponent>(getScores[i].playerWon + " - " + std::to_string(getScores[i].score))->SetPosition(300.f, 260.f + (i * 30));
	}



	endingScene.Add(std::move(scoretext));
}
Highscores::highscoreData LevelObserver::GetEndData()
{
	int endScore{0};
	std::string playerWon{"Player 1"};

	//delete the players if they exist
	auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	auto player1 = scene->FindGameObjectByTag("p1");
	if (player1) {
		endScore += player1->GetComponent<booble::Player>()->GetScore();
		player1->SetToDelete();
	}

	switch (static_cast<booble::GameMode>(booble::GameLoader::GetInstance().GetSelectedGamemode()))
	{
		case booble::GameMode::MULTIPLAYER:
		{
			//get player 2 and delete it
			auto player2 = scene->FindGameObjectByTag("p2");
			if (!player2) break;

			//get score from player 2
			int scorePlayer2 = player2->GetComponent<booble::Player>()->GetScore();

			//this is versus so check which player won and that will be the end score
			if (endScore < scorePlayer2) {
				endScore = scorePlayer2;
				playerWon = "Player 2"; //player 2 won
			}
			player2->SetToDelete();

			break;
		}
		case booble::GameMode::COOP:
		{
			playerWon = "Both players";

			//get player 2 and delete it
			auto player2 = scene->FindGameObjectByTag("p2");
			if (!player2) break;
			

			//scores combine /2 to make the leaderboard fair

			endScore += player2->GetComponent<booble::Player>()->GetScore();
			endScore /= 2;

			player2->SetToDelete();

			break;
		}
	}

	return Highscores::highscoreData{playerWon, endScore};
}
