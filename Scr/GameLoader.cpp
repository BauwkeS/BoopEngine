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
#include "Components/TankGun.h"

namespace booble
{
	void GameLoader::RegisterGameObjectTypes()
	{
		RegisterAirType();
		RegisterWallType();
		RegisterWallBorderType();
		RegisterPlayerType("RedTank.png", "p1", 50);
		RegisterPlayerType("GreenTank.png", "p2", 50);
		RegisterEnemyType("BlueTank.png", "enemy", 0);
	}

	void GameLoader::RegisterAirType()
	{
		level::LevelLoader::GetInstance().RegisterType(2, level::LevelLayer::STATIC)
			.AddComponent<boop::TextureComponent>("path.png");
	}

	void GameLoader::RegisterWallType()
	{
		level::LevelLoader::GetInstance().RegisterType(0, level::LevelLayer::STATIC)
			.AddComponent<boop::TextureComponent>("wall.png")
			.SetDefaultTag("collision");
	}

	void GameLoader::RegisterWallBorderType()
	{
		level::LevelLoader::GetInstance().RegisterType(1, level::LevelLayer::STATIC)
			.AddComponent<boop::TextureComponent>("void.png");
	}

	void GameLoader::RegisterPlayerType(const std::string& spritePath, const std::string& tagName, int playerSpeed)
	{
		//TO-DO ADD WHAT BLOCK IT LEAVES BEHIND


		int index = (tagName == "p1") ? 5 : 6; // Assign indices for players
		auto& playerType = level::LevelLoader::GetInstance().RegisterType(index, level::LevelLayer::PERSISTENT, 2)
			.AddComponent<Health>(4)
			.AddComponent<BaseTank>(playerSpeed, spritePath)
			.AddComponent<Player>()
			.SetDefaultTag(tagName);

		// Create a child type that will hold the Level component
		auto levelChildType = std::make_unique<boop::GameObjectType>();
		levelChildType->SetDefaultTag("level"); // Unique tag for the level child

		// Add the Level component to the child
		levelChildType->AddComponent<Level>();


		// Create tank gun child
		auto tankGunChildType = std::make_unique<boop::GameObjectType>();
		tankGunChildType->SetDefaultTag("tankgun");
		if(index==5) tankGunChildType->AddComponent<TankGun>("RedTankGun.png");
		else tankGunChildType->AddComponent<TankGun>("GreenTankGun.png");
		tankGunChildType->SetLocalPosition(-10,-8);


		// Add the child type to the player type
		playerType.AddChildType(std::move(levelChildType));
		playerType.AddChildType(std::move(tankGunChildType));
	}

	void GameLoader::RegisterEnemyType(const std::string& spritePath, const std::string& tagName, int playerSpeed)
	{
		level::LevelLoader::GetInstance().RegisterType(4, level::LevelLayer::DYNAMIC)
			.AddComponent<Enemy>(playerSpeed, spritePath)
			.SetDefaultTag(tagName);
	}

	void GameLoader::MakeLevel(const std::string& levelPath, const std::string& levelName)
	{
		level::LevelLoader::GetInstance().CreateLevel(levelPath, levelName);
		auto* level = boop::SceneManager::GetInstance().GetScene(levelName);
		assert(level);

		//player1
		auto* player1 = level->FindGameObjectByTag("p1")->GetComponent<Player>();
		assert(player1);
		//player2
		auto* player2 = level->FindGameObjectByTag("p2")->GetComponent<Player>();
		assert(player2);

		player1->AddKeyboardMovement();
		//TO-DO REMOVE THIS PIECE OF SHI


		//set the UI position
		player1->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 200);
		player1->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 250);

		//set observers
		player1->GetOwner()->GetChildAt(0)->GetComponent<Level>()->GetSubject()->AddObserver(player1);

		switch (static_cast<booble::GameMode>(m_selectedGamemode)) {
		case booble::GameMode::SINGLEPLAYER:
		{
			//remove p2 out of the level
			player2->GetOwner()->SetToDelete();
			break;
		}
		case booble::GameMode::MULTIPLAYER:
		{
			//input player 2
			player2->AddControllerMovement();
			player1->AddControllerMovement(); // if there is a second controller, the first player can also use it

			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 500);
			player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);

			//set observers
			player2->GetOwner()->GetChildAt(0)->GetComponent<Level>()->GetSubject()->AddObserver(player2);

			break;
		}
		case booble::GameMode::COOP:
		{
			//to-do update this for being an enemy after enemies are done
			//input player 2
			player2->AddControllerMovement();
			player1->AddControllerMovement(); // if there is a second controller, the first player can also use it

			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 500);
			player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);

			//set observers
			player2->GetOwner()->GetChildAt(0)->GetComponent<Level>()->GetSubject()->AddObserver(player2);

			break;
			break;
		}
		}
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
		boop::InputManager::GetInstance().AddCommand(SDL_SCANCODE_SPACE, boop::keyState::isDown,
			std::make_unique<booble::StartGame>(this), levelName);
		boop::InputManager::GetInstance().AddCommand(SDL_SCANCODE_TAB, boop::keyState::isDown,
			std::make_unique<booble::ChangeGamemodeSelection>(selectionText.get(), this), levelName);
		//controller commands
		boop::InputManager::GetInstance().AddController();
		boop::InputManager::GetInstance().AddCommand(static_cast<int>(boop::Controller::ControllerId::First),
			boop::Controller::ControllerButton::ButtonA, boop::keyState::isDown,
			std::make_unique<booble::StartGame>(this), levelName);
		boop::InputManager::GetInstance().AddCommand(static_cast<int>(boop::Controller::ControllerId::First),
			boop::Controller::ControllerButton::ButtonY, boop::keyState::isDown,
			std::make_unique<booble::ChangeGamemodeSelection>(selectionText.get(), this), levelName);

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
		//RESET CONTROLLERS
		boop::InputManager::GetInstance().DeleteControllers();

		//CREATE LEVELS
		MakeLevel("levels/level1.txt", "level1");
		MakeLevel("levels/level2.txt", "level2");
		MakeLevel("levels/level3.txt", "level3");
	}

}