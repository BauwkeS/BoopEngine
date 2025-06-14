#pragma once
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
		//sound
		boop::ServiceLocator::GetSoundSystem()->StopAll();
		boop::ServiceLocator::GetSoundSystem()->PlaySound("FailMusic.wav", 0.5f);

		//set up the end screen
		boop::InputManager::GetInstance().ClearCommands();
		SetEndData();

		MakeInputEndScreen();

		auto changeScene = booble::ChangeScene("InputEndingScreen");
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

	m_Highscores->AddHighScore(m_EndData);

	//selection info
	auto mainTexts = std::make_unique<boop::GameObject>();
	mainTexts->AddComponent<boop::TextComponent>("GAME OVER: " + m_EndData.playerWon + " won!")->SetPosition(300, 100);
	mainTexts->AddComponent<boop::TextComponent>("With score: " + std::to_string(m_EndData.score))->SetPosition(300, 200);

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
void LevelObserver::SetWinningScore()
{
	//--SCORE
	int endScore{ 0 };

	//delete the players if they exist
	auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	auto player1 = scene->FindGameObjectByTag("p1");
	if (player1) {
		endScore += player1->GetComponent<booble::Player>()->GetScore();
		player1->SetToDelete();
	}

	//get player 2 and delete it
	auto player2 = scene->FindGameObjectByTag("p2");
	if (player2) {
		//get score from player 2
		int scorePlayer2 = player2->GetComponent<booble::Player>()->GetScore();

		//this is versus so check which player won and that will be the end score
		if (endScore < scorePlayer2) {
			endScore = scorePlayer2;
		}
		player2->SetToDelete();
	}


	m_EndData.score = endScore;
}
void LevelObserver::SetEndData()
{
	SetWinningScore();
	SetWinningPlayer();
}
void LevelObserver::SetWinningPlayer()
{
	//--PLAYER
	//get player from the 3 input letters
	std::string playerWon;
	for (int i = 0; i < 3; ++i)
	{
		playerWon += std::string(1,m_Letters[m_LetterIndexes[i]]);
	}

	m_EndData.playerWon = playerWon;
}


void LevelObserver::MakeInputEndScreen()
{
	//just the player input here to make the name

	//SETUP
	const std::string levelName{ "InputEndingScreen" };
	auto& endingScene = boop::SceneManager::GetInstance().AddScene(levelName);

	std::string letter1(1, m_Letters[m_LetterIndexes[0]]);
	std::string letter2(1, m_Letters[m_LetterIndexes[1]]);
	std::string letter3(1, m_Letters[m_LetterIndexes[2]]);

	//selection info
	auto mainTexts = std::make_unique<boop::GameObject>();
	mainTexts->AddComponent<boop::TextComponent>("Select Name: ")->SetPosition(300, 100);
	auto slectionText = std::make_unique<boop::GameObject>();
	slectionText->AddComponent<boop::TextComponent>(letter1)->SetPosition(300, 170);
	slectionText->AddComponent<boop::TextComponent>(letter2)->SetPosition(330, 170);
	slectionText->AddComponent<boop::TextComponent>(letter3)->SetPosition(360, 170);
	slectionText->SetTag("selection");
	mainTexts->AddComponent<boop::TextComponent>("Use arrow keys/buttons:")->SetPosition(200, 300);
	mainTexts->AddComponent<boop::TextComponent>("- up/down to change letter")->SetPosition(200, 330);
	mainTexts->AddComponent<boop::TextComponent>("- left right to switch letter ")->SetPosition(200, 360);
	mainTexts->AddComponent<boop::TextComponent>("Press enter/A to continue")->SetPosition(200, 400);

	//---
	//INPUT

	//keyboard
	boop::InputManager::GetInstance().AddCommand(SDL_SCANCODE_RETURN, boop::keyState::isDown,
		std::make_unique<GoToEndScreen>(this));

	boop::InputManager::GetInstance().AddCommand(SDL_SCANCODE_UP, boop::keyState::isDown,
		std::make_unique<ChangeLetter>(this, m_LetterIndexes, m_SelectedLetter, true));
	boop::InputManager::GetInstance().AddCommand(SDL_SCANCODE_DOWN, boop::keyState::isDown,
		std::make_unique<ChangeLetter>(this, m_LetterIndexes, m_SelectedLetter, false));
	boop::InputManager::GetInstance().AddCommand(SDL_SCANCODE_RIGHT, boop::keyState::isDown,
		std::make_unique<ChangeSelection>(m_SelectedLetter, true));
	boop::InputManager::GetInstance().AddCommand(SDL_SCANCODE_LEFT, boop::keyState::isDown,
		std::make_unique<ChangeSelection>(m_SelectedLetter, false));

	//controller
	boop::InputManager::GetInstance().AddCommand(static_cast<int>(boop::Controller::ControllerId::First),
		boop::Controller::ControllerButton::ButtonA, boop::keyState::isDown,
		std::make_unique<GoToEndScreen>(this));;

	boop::InputManager::GetInstance().AddCommand(static_cast<int>(boop::Controller::ControllerId::First),
		boop::Controller::ControllerButton::DPadDown, boop::keyState::isDown,
		std::make_unique<ChangeLetter>(this, m_LetterIndexes, m_SelectedLetter, true));
	boop::InputManager::GetInstance().AddCommand(static_cast<int>(boop::Controller::ControllerId::First),
		boop::Controller::ControllerButton::DPadUp, boop::keyState::isDown,  
		std::make_unique<ChangeLetter>(this, m_LetterIndexes, m_SelectedLetter, false));
	boop::InputManager::GetInstance().AddCommand(static_cast<int>(boop::Controller::ControllerId::First),
		boop::Controller::ControllerButton::DPadRight, boop::keyState::isDown,
		std::make_unique<ChangeSelection>(m_SelectedLetter, true));
	boop::InputManager::GetInstance().AddCommand(static_cast<int>(boop::Controller::ControllerId::First),
		boop::Controller::ControllerButton::DPadLeft, boop::keyState::isDown,
		std::make_unique<ChangeSelection>(m_SelectedLetter, false));



	endingScene.Add(std::move(slectionText));
	endingScene.Add(std::move(mainTexts));
}


//-------------------
void ChangeLetter::Execute()
{
	// Update the text
	if (!m_MoveUp) m_Letters[m_SelectedLetter] = (m_Letters[m_SelectedLetter] + 1) % 26; // Wrap around after 'Z'
	else m_Letters[m_SelectedLetter] = (m_Letters[m_SelectedLetter] - 1 + 26) % 26; // Wrap around before 'A'

	auto letters = m_pGameObject->GetLetters();

	auto textGO = boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("selection");
	auto textsC = textGO->GetSomeComponent<boop::TextComponent>();

	textsC[m_SelectedLetter]->SetText(std::string(1, m_pGameObject->GetLetters()[m_Letters[m_SelectedLetter]]));
}

void ChangeSelection::Execute()
{
	if (m_MoveUp) m_Letterindex = (m_Letterindex + 1) % 3; 
	else m_Letterindex = (m_Letterindex - 1 + 3) % 3;
}

void GoToEndScreen::Execute()
{
	m_pLevelObs->SetWinningPlayer();
	m_pLevelObs->SetUpEndScreen();
	booble::ChangeScene changeScene("EndingScreen");
	changeScene.Execute();
}
