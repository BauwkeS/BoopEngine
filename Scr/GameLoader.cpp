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
	void GameLoader::RegisterGameObjectTypes()
	{
		RegisterAirType();
		//RegisterWallType(0); // Purple block
		RegisterWallType(1); // Stone block
		RegisterPlatformType(0); // Purple block
		//RegisterPlatformType(1); // Stone block
		RegisterPlayerType("RedTank.png", "p1", 200);
		RegisterPlayerType("GreenTank.png", "p2", 200);
		RegisterEnemyType("BlueTank.png", "enemy", 400);
	}

	void GameLoader::RegisterAirType()
	{
		level::LevelLoader::GetInstance().RegisterType(0, level::LevelLayer::STATIC)
			.AddComponent<boop::TextureComponent>("", 4.f);
	}

	void GameLoader::RegisterWallType(int whichBlock)
	{
		const std::string texture = (whichBlock == 0) ? "purpleBlock.png" : "stoneBlock.png";
		level::LevelLoader::GetInstance().RegisterType(1, level::LevelLayer::STATIC)
			.AddComponent<boop::TextureComponent>(texture, 4.f)
			.SetDefaultTag("collision");
	}

	void GameLoader::RegisterPlatformType(int whichBlock)
	{
		const std::string texture = (whichBlock == 0) ? "purpleBlock.png" : "stoneBlock.png";
		level::LevelLoader::GetInstance().RegisterType(2 , level::LevelLayer::STATIC)
			.AddComponent<boop::TextureComponent>(texture, 4.f)
			.SetDefaultTag("Platform");
	}

	void GameLoader::RegisterPlayerType(const std::string& spritePath, const std::string& tagName, int playerSpeed)
	{
		int index = (tagName == "p1") ? 3 : 4; // Assign indices for players
		level::LevelLoader::GetInstance().RegisterType(index, level::LevelLayer::PERSISTENT)
			.AddComponent<Player>(playerSpeed, spritePath)
			.SetDefaultTag(tagName);
	}

	void GameLoader::RegisterEnemyType(const std::string& spritePath, const std::string& tagName, int playerSpeed)
	{
		level::LevelLoader::GetInstance().RegisterType(5, level::LevelLayer::DYNAMIC)
			.AddComponent<Enemy>(playerSpeed, spritePath)
			.SetDefaultTag(tagName);
	}

	void GameLoader::MakeLevelOne()
	{
		const std::string levelOne{ "LevelOne" };
		level::LevelLoader::GetInstance().CreateLevel("level1/level1_" + std::to_string(m_selectedGamemode) + ".txt", levelOne);
		//set up the selected gamemode with whats needed for players

		auto* sceneLvl1 = boop::SceneManager::GetInstance().GetScene(levelOne);
		assert(sceneLvl1);

		//--LEVEL SPECIFICS--
		//player controls info
		auto howToPlay = std::make_unique<boop::GameObject>();
		howToPlay->AddComponent<boop::TextComponent>("Use D-Pad to move the blue tank, X to inflict damage, A and B to kill a tank")->SetPosition(0,50);
		howToPlay->AddComponent<boop::TextComponent>("Use WASD to move the green tank, C to inflict damage, Z and X to kill a tank")->SetPosition(0,70);
		sceneLvl1->Add(std::move(howToPlay));		
		
		auto* player1GO = sceneLvl1->FindGameObjectByTag("p1");
		if (!player1GO) {
			throw std::runtime_error("Player1 GameObject not found!");
		}

		auto* player1 = player1GO->GetComponent<Player>();
		if (!player1) {
			// Debug what components actually exist
			std::cout << "Player1 GameObject has these components:\n";
			for (const auto& comp : player1GO->GetAllComponents()) {
				std::cout << typeid(*comp).name() << "\n";
			}
			throw std::runtime_error("Player component not found on Player1 GameObject!");
		}


		//player1->GetTankBase()->SetStartPos(player1GO->GetWorldPosition());
		player1->AddKeyboardMovement(levelOne);
		
		//set the UI position
		player1->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 200);
		player1->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 250);


		////level component
		//auto levelItems = std::make_unique<boop::GameObject>();
		//auto levelComp = levelItems->AddComponent<Level>(sceneLvl1, m_selectedGamemode);
		//levelComp->GetPlayer1Sub()->AddObserver(player1);
		
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

			//levelComp->GetPlayer2Sub()->AddObserver(player2);

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

			//levelComp->GetPlayer2Sub()->AddObserver(player2);

			break;
		}
		}

		//sceneLvl1->Add(std::move(levelItems));

		
	}

	void GameLoader::MakeLevelTwo()
	{
		//TESTING

		level::LevelLoader::GetInstance().CreateLevel("level1/level1_3.txt", "level1_0");
		auto* testlvl = boop::SceneManager::GetInstance().GetScene("level1_0");

		//input player 1 
		auto* player1GO = testlvl->FindGameObjectByTag("p1");
		auto* player1 = player1GO->GetComponent<Player>();
		assert(player1);
		//player1->GetTankBase()->SetStartPos(player1GO->GetWorldPosition());
		player1->AddKeyboardMovement( "level1_0");

		//set the UI position
		player1->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 200);
		player1->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 250);

		//level component
		/*auto levelItems = std::make_unique<boop::GameObject>();
		auto levelComp = levelItems->AddComponent<Level>(testlvl, m_selectedGamemode);*/
		//levelComp->GetPlayer1Sub()->AddObserver(player1);

		switch (static_cast<booble::GameMode>(m_selectedGamemode)) {
		case booble::GameMode::MULTIPLAYER:
		{

			//input player 2
			auto* player2GO = testlvl->FindGameObjectByTag("p2");
			auto* player2 = player2GO->GetComponent<Player>();
			assert(player2);
			//player2->GetTankBase()->SetStartPos(player2GO->GetWorldPosition());
			player2->AddControllerMovement("level1_0");
			player1->AddControllerMovement("level1_0"); // if there is a second controller, the first player can also use it

			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 500);
			player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);

		//levelComp->GetPlayer2Sub()->AddObserver(player2);

			break;
		}
		case booble::GameMode::COOP:
		{

			//input player 2
			auto* player2GO = testlvl->FindGameObjectByTag("p2");
			auto* player2 = player2GO->GetComponent<Player>();
			assert(player2);
			//player2->GetTankBase()->SetStartPos(player2GO->GetWorldPosition());
			player2->AddControllerMovement("level1_0");
			player1->AddControllerMovement("level1_0"); // if there is a second controller, the first player can also use it

			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 500);
			player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);

			//levelComp->GetPlayer2Sub()->AddObserver(player2);

			break;
		}
		}

		


		//testlvl->Add(std::move(levelItems));


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
		//REGISTER OBJECTS
		RegisterGameObjectTypes();


		//CREATE MAIN SCREEN
		MakeMainScreen();

		//LOAD LEVEL
		boop::SceneManager::GetInstance().ChangeScene("MainScreen");
	}

	void GameLoader::InitializeLevels()
	{
		//CREATE LEVELS
		MakeLevelOne();
		MakeLevelTwo();
	}

}