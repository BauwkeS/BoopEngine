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

#include "../BoopEngine/Boop/Sound/ServiceLocator.h"

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
		RegisterDiamondType();
		RegisterPlayerType("RedTank.png", "p1", 50);
		RegisterPlayerType("GreenTank.png", "p2", 50);
		RegisterBlueTankEnemy("BlueTank.png", "enemy", 30);
		RegisterRecognizerEnemy("Recognizer.png", "enemy", 60);
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

	void GameLoader::RegisterDiamondType()
	{
		level::LevelLoader::GetInstance().RegisterType(3, level::LevelLayer::STATIC)
			.AddComponent<boop::TextureComponent>("teleport.png")
			.SetDefaultTag("diamond");
	}

	void GameLoader::RegisterPlayerType(const std::string& spritePath, const std::string& tagName, int playerSpeed)
	{
		int index = (tagName == "p1") ? 5 : 6; // Assign indices for players
		auto& playerType = level::LevelLoader::GetInstance().RegisterType(index, level::LevelLayer::PERSISTENT)
			.SetObjectUnder(2) // Set the object under index to 2 (air type)
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

	void GameLoader::RegisterRecognizerEnemy(const std::string& spritePath, const std::string& tagName, int playerSpeed)
	{
		level::LevelLoader::GetInstance().RegisterType(7, level::LevelLayer::DYNAMIC)
			.SetObjectUnder(1)
			.AddComponent<BaseTank>(playerSpeed, spritePath)
			.AddComponent<RecognizerEnemy>()
			.AddComponent<Health>(1)
			.SetDefaultTag(tagName);
	}

	void GameLoader::RegisterBlueTankEnemy(const std::string& spritePath, const std::string& tagName, int playerSpeed)
	{
		level::LevelLoader::GetInstance().RegisterType(4, level::LevelLayer::DYNAMIC)
			.SetObjectUnder(1)
			.AddComponent<BaseTank>(playerSpeed, spritePath)
			.AddComponent<BlueTankEnemy>()
			.AddComponent<Health>(3)
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

		//set score observsers and merge if needed
		auto scoreObsPlayer1 = player1->GetOwner()->AddComponent<ScoreObserver>();
		player1->GetSubject()->AddObserver(scoreObsPlayer1);
		player1->GetSubject()->AddObserver(m_levelObserver.get());

		//set the UI position
		player1->GetOwner()->GetComponent<HealthObserver>()->SetPosition(600, 200);
		player1->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(600, 250);

		//set observers
		player1->GetOwner()->GetChildAt(0)->GetComponent<Level>()->GetSubject()->AddObserver(player1);
		player1->GetOwner()->GetComponent<Health>()->GetSubject()->AddObserver(m_levelObserver.get());

		switch (static_cast<booble::GameMode>(m_selectedGamemode)) {
		case booble::GameMode::SINGLEPLAYER:
		{
			//remove p2 out of the level
			player2->GetOwner()->SetToDelete();
			player1->AddControllerMovement();

			break;
		}
		case booble::GameMode::MULTIPLAYER:
		{
			//input player 2
			player2->AddControllerMovement();
			player1->AddControllerMovement();

			//set observers
			player2->GetOwner()->GetChildAt(0)->GetComponent<Level>()->GetSubject()->AddObserver(player2);
			player2->GetOwner()->GetComponent<Health>()->GetSubject()->AddObserver(m_levelObserver.get());

			//score
			auto scoreObsPlayer2 = player2->GetOwner()->AddComponent<ScoreObserver>();
			player2->GetSubject()->AddObserver(scoreObsPlayer2);
			player2->GetSubject()->AddObserver(m_levelObserver.get());

			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(600, 500);
			player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(600, 550);

			break;
		}
		case booble::GameMode::COOP:
		{
			//to-do update this for being an enemy after enemies are done
			//input player 2
			player2->AddControllerMovement();
			player1->AddControllerMovement();

			//merge the score from player2 to player1
			player2->GetSubject()->AddObserver(scoreObsPlayer1);
			player2->GetSubject()->AddObserver(m_levelObserver.get());

			//set observers
			player2->GetOwner()->GetChildAt(0)->GetComponent<Level>()->GetSubject()->AddObserver(player2);
			player2->GetOwner()->GetComponent<Health>()->GetSubject()->AddObserver(m_levelObserver.get());


			//set the UI position
			player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(600, 500);
			//player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);


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

	//void GameLoader::MakeEndingScreen()
	//{
	//	////SETUP
	//	//const std::string levelName{ "EndingScreen" };
	//	//auto& sceneMain = boop::SceneManager::GetInstance().AddScene(levelName);

	//	////selection info
	//	//auto mainMenuText = std::make_unique<boop::GameObject>();
	//	//mainMenuText->AddComponent<boop::TextComponent>("GAME OVER:?")->SetPosition(300, 100);
	//	//mainMenuText->AddComponent<boop::TextComponent>("Yesyes the end")->SetPosition(300, 300);

	//	//sceneMain.Add(std::move(mainMenuText));
	//}

	void GameLoader::MakeGame()
	{
		//REGISTER OBJECTS
		RegisterGameObjectTypes();


		//CREATE MAIN SCREEN
		MakeMainScreen();

		//LOAD LEVEL
		boop::SceneManager::GetInstance().ChangeScene("MainScreen");

		//SET MUSIC
		boop::ServiceLocator::RegisterSoundSystem(std::make_unique<boop::SDL2SoundSystem>());
		boop::ServiceLocator::GetSoundSystem()->PlaySound("MainMenuMusic.wav", 0.5f);
	}

	void GameLoader::InitializeLevels()
	{
		//Level control
		m_levelObserver = std::make_unique<LevelObserver>();

		//RESET CONTROLLERS
		boop::InputManager::GetInstance().DeleteControllers();

		//CREATE LEVELS
		MakeLevel("levels/level1.txt", "level1");
		MakeLevel("levels/level2.txt", "level2");
		MakeLevel("levels/level3.txt", "level3");

		//MakeEndingScreen();
	}

}