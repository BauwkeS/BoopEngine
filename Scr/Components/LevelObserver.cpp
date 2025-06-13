#include "LevelObserver.h"
#include "../../BoopEngine/Boop/GameObject.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../GameCommands.h"
#include "../GameLoader.h"

LevelObserver::LevelObserver()
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

	EndData endData = GetEndData();

	//selection info
	auto mainTexts = std::make_unique<boop::GameObject>();
	mainTexts->AddComponent<boop::TextComponent>("GAME OVER: " + endData.playerWon + " won!")->SetPosition(300, 100);
	mainTexts->AddComponent<boop::TextComponent>("With score: " + endData.score)->SetPosition(300, 200);











	endingScene.Add(std::move(mainTexts));
}

LevelObserver::EndData LevelObserver::GetEndData()
{
	int endScore{};
	std::string playerWon{"Player 1"};

	//delete the players if they exist
	auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	auto player1 = scene->FindGameObjectByTag("p1");
	if (player1) {
		player1->SetToDelete();
		endScore = player1->GetComponent<booble::Player>()->GetScore();
	}

	switch (static_cast<booble::GameMode>(booble::GameLoader::GetInstance().GetSelectedGamemode()))
	{
		case booble::GameMode::MULTIPLAYER:
		{
			//get player 2 and delete it
			auto player2 = scene->FindGameObjectByTag("p2");
			if (!player2) break;

			player2->SetToDelete();
			//get score from player 2
			int scorePlayer2 = player2->GetComponent<booble::Player>()->GetScore();

			//this is versus so check which player won and that will be the end score
			if (endScore < scorePlayer2) {
				endScore = scorePlayer2;
				playerWon = "Player 2"; //player 2 won
			}
			break;
		}
		case booble::GameMode::COOP:
		{
			playerWon = "Both players";

			//get player 2 and delete it
			auto player2 = scene->FindGameObjectByTag("p2");
			if (!player2) break;
			
			player2->SetToDelete();

			//scores combine /2 to make the leaderboard fair

			endScore += player2->GetComponent<booble::Player>()->GetScore();
			endScore /= 2;

			break;
		}
	}

	return EndData{endScore,playerWon};
}
