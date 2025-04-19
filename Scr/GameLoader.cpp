#pragma once
#include "GameLoader.h"
#include <memory>

#include "GameCommands.h"
#include "../BoopEngine/Boop/Scene/LevelLoader.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/Scene/Scene.h"
#include "../BoopEngine/Boop/GameObject.h"

#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../BoopEngine/Boop/Input/InputManager.h"

#include "Components/player.h"
#include "Components/Health.h"
#include "Components/HealthObserver.h"
#include "Components/ScoreObserver.h"

#include "Level.h"
#include "Components/Enemy.h"

namespace booble
{
	std::unique_ptr<boop::GameObject> GameLoader::CreateAir()
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent< boop::TextureComponent>( "", 4.f);
		return std::move(gameObjPtr);
	}
	std::unique_ptr<boop::GameObject> GameLoader::CreateWall(int whichBlock)
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		if (whichBlock == 0) {
			gameObjPtr->AddComponent< boop::TextureComponent>("purpleBlock.png", 4.f);
		}
		else {
			gameObjPtr->AddComponent< boop::TextureComponent>("stoneBlock.png", 4.f);
		}
		gameObjPtr->SetTag("collision");

		return std::move(gameObjPtr);
	}

	std::unique_ptr<boop::GameObject> GameLoader::CreatePlatform(int whichBlock)
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		if (whichBlock == 0) {
			gameObjPtr->AddComponent<boop::TextureComponent>("purpleBlock.png", 4.f);
		}
		else {
			gameObjPtr->AddComponent< boop::TextureComponent>("stoneBlock.png", 4.f);
		}

		gameObjPtr->SetTag("Platform");

		return std::move(gameObjPtr);
	}

	std::unique_ptr<boop::GameObject> GameLoader::CreatePlayer(const std::string spritePath, const std::string tagName, int playerSpeed)
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		playerObject->SetTag(tagName); //add tag for level

		playerObject->AddComponent<Player>(playerSpeed, spritePath); // add base player comp

		return std::move(playerObject);
	}

	std::unique_ptr<boop::GameObject> GameLoader::CreateEnemy(const std::string spritePath, const std::string tagName, int playerSpeed)
	{
		auto enemyObject = std::make_unique<boop::GameObject>();
		enemyObject->SetTag(tagName); //add tag for level

		enemyObject->AddComponent<Enemy>(playerSpeed, spritePath); // add base player comp

		return std::move(enemyObject);
	}

	void GameLoader::MakeLevelOne()
	{
		const std::string levelOne{ "LevelOne" };
		level::LevelLoader::GetInstance().CreateLevel("level1/level1_" + std::to_string(m_selectedGamemode) + ".txt", levelOne);
		//set up the selected gamemode with whats needed for players

		//switch (static_cast<booble::GameMode>(m_selectedGamemode)) {
		//case booble::GameMode::SINGLEPLAYER:

		//	//SETUP LEVEL
		//	

		//	break;
		//case booble::GameMode::MULTIPLAYER:
		//	
		//	//SETUP LEVEL
		//	level::LevelLoader::GetInstance().CreateLevel("level1/level1_multi.txt", levelOne);

		//	break;
		//case booble::GameMode::COOP:

		//	//SETUP LEVEL
		//	level::LevelLoader::GetInstance().CreateLevel("level1/level1_coop.txt", levelOne);
		//	
		//	break;
		//}
		auto* sceneLvl1 = boop::SceneManager::GetInstance().GetScene(levelOne);
		assert(sceneLvl1);

		//--LEVEL SPECIFICS--
		//player controls info
		auto howToPlay = std::make_unique<boop::GameObject>();
		howToPlay->AddComponent<boop::TextComponent>("Use D-Pad to move the blue tank, X to inflict damage, A and B to kill a tank")->SetPosition(0,50);
		howToPlay->AddComponent<boop::TextComponent>("Use WASD to move the green tank, C to inflict damage, Z and X to kill a tank")->SetPosition(0,70);
		sceneLvl1->Add(std::move(howToPlay));



		//input player 1 
		auto* player1GO = sceneLvl1->FindGameObjectByTag("p1");
		auto* player1 = player1GO->GetComponent<Player>();
		assert(player1);
		//player1->GetTankBase()->SetStartPos(player1GO->GetWorldPosition());
		player1->AddKeyboardMovement(levelOne);
		
		//set the UI position
		player1->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 200);
		player1->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 250);


		//level component
		auto levelItems = std::make_unique<boop::GameObject>();
		auto levelComp = levelItems->AddComponent<Level>(sceneLvl1, m_selectedGamemode);
		levelComp->GetPlayer1Sub()->AddObserver(player1);
		


		switch (static_cast<booble::GameMode>(m_selectedGamemode)) {
		case booble::GameMode::MULTIPLAYER:
		{

			//input player 2
			auto* player2GO = sceneLvl1->FindGameObjectByTag("p2");
			auto* player2 = player2GO->GetComponent<Player>();
			assert(player2);
			//player2->GetTankBase()->SetStartPos(player2GO->GetWorldPosition());
			player2->AddControllerMovement(levelOne);
			player1->AddControllerMovement(levelOne); // if there is a second controller, the first player can also use it

			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 500);
			player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);

			levelComp->GetPlayer2Sub()->AddObserver(player2);

			break;
		}
		case booble::GameMode::COOP:
		{

			//input player 2
			auto* player2GO = sceneLvl1->FindGameObjectByTag("p2");
			auto* player2 = player2GO->GetComponent<Player>();
			assert(player2);
			//player2->GetTankBase()->SetStartPos(player2GO->GetWorldPosition());
			player2->AddControllerMovement(levelOne);
			player1->AddControllerMovement(levelOne); // if there is a second controller, the first player can also use it

			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 500);
			player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);

			levelComp->GetPlayer2Sub()->AddObserver(player2);

			break;
		}
		}

		sceneLvl1->Add(std::move(levelItems));

		

		
	}

	void GameLoader::MakeMainScreen()
	{
		//SETUP
		const std::string levelName{ "MainScreen" };
		auto& sceneMain = boop::SceneManager::GetInstance().AddScene(levelName);
		
		//selection info
		auto mainMenuText = std::make_unique<boop::GameObject>();
		mainMenuText->AddComponent<boop::TextComponent>("A/SPACE to start")->SetPosition(300,100);
		mainMenuText->AddComponent<boop::TextComponent>("Y/TAB to change")->SetPosition(300,300);

		auto selectionText = std::make_unique<boop::GameObject>();
		selectionText->AddComponent<boop::TextComponent>("Gamemode: SINGLEPLAYER")->SetPosition(300, 330);


		//keyboard commands
		boop::InputManager::GetInstance().AddCommand(levelName, SDL_SCANCODE_SPACE, boop::keyState::isDown,
			std::make_unique<booble::StartGame>(this));
		boop::InputManager::GetInstance().AddCommand(levelName, SDL_SCANCODE_TAB, boop::keyState::isDown,
			std::make_unique<booble::ChangeGamemodeSelection>(selectionText.get(), this));
		//controller commands
		boop::InputManager::GetInstance().AddController();
		boop::InputManager::GetInstance().AddCommand(levelName, static_cast<int>(boop::Controller::ControllerId::First),
			boop::Controller::ControllerButton::ButtonA, boop::keyState::isDown, std::make_unique<booble::StartGame>(this));
		boop::InputManager::GetInstance().AddCommand(levelName, static_cast<int>(boop::Controller::ControllerId::First),
			boop::Controller::ControllerButton::ButtonY, boop::keyState::isDown, std::make_unique<booble::ChangeGamemodeSelection>(selectionText.get(), this));

		sceneMain.Add(std::move(mainMenuText));
		sceneMain.Add(std::move(selectionText));
	}

	void GameLoader::MakeGame()
	{
		//CREATE GAME OBJECTS
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(CreateAir()), level::LevelLayer::STATIC);
		level::LevelLoader::GetInstance().AssignGameObject(1, std::move(CreateWall(0)), level::LevelLayer::STATIC);
		level::LevelLoader::GetInstance().AssignGameObject(2, std::move(CreatePlatform(0)), level::LevelLayer::STATIC);
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(CreatePlayer("RedTank.png", "p1",200)), level::LevelLayer::PERSISTENT);
		level::LevelLoader::GetInstance().AssignGameObject(4, std::move(CreatePlayer("GreenTank.png", "p2", 200)), level::LevelLayer::PERSISTENT);
		level::LevelLoader::GetInstance().AssignGameObject(5, std::move(CreateEnemy("BlueTank.png", "enemy",400)), level::LevelLayer::DYNAMIC);

		//Set important tags
		std::vector<std::string> importantTags;
		importantTags.emplace_back("p1");
		importantTags.emplace_back("p2");
		level::LevelLoader::GetInstance().SetImportantTags(importantTags);

		//CREATE MAIN SCREEN
		MakeMainScreen();

		//LOAD LEVEL
		boop::SceneManager::GetInstance().ChangeScene("MainScreen");
	}

	void GameLoader::InitializeLevels()
	{
		//CREATE LEVELS
		MakeLevelOne();
	}

}