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

namespace booble
{
	std::unique_ptr<boop::GameObject> GameLoader::CreateAir()
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent< boop::TextureComponent>(nullptr, "", 4.f);
		return std::move(gameObjPtr);
	}
	std::unique_ptr<boop::GameObject> GameLoader::CreateWall(int whichBlock)
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		if (whichBlock == 0) {
			gameObjPtr->AddComponent< boop::TextureComponent>(nullptr, "purpleBlock.png", 4.f);
		}
		else {
			gameObjPtr->AddComponent< boop::TextureComponent>(nullptr, "stoneBlock.png", 4.f);
		}
		gameObjPtr->SetTag("Wall");

		return std::move(gameObjPtr);
	}

	std::unique_ptr<boop::GameObject> GameLoader::CreatePlatform(int whichBlock)
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		if (whichBlock == 0) {
			gameObjPtr->AddComponent<boop::TextureComponent>(nullptr, "purpleBlock.png", 4.f);
		}
		else {
			gameObjPtr->AddComponent< boop::TextureComponent>(nullptr, "stoneBlock.png", 4.f);
		}

		gameObjPtr->SetTag("Platform");

		return std::move(gameObjPtr);
	}

	std::unique_ptr<boop::GameObject> GameLoader::CreatePlayer(const std::string spritePath, const std::string tagName, int playerSpeed)
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		playerObject->SetTag(tagName); //add tag for level

		auto playerComp = playerObject->AddComponent<Player>(nullptr, playerSpeed, spritePath); // add base player comp

		//level brain
		auto levelComp = playerObject->AddComponent<Level>(nullptr);
		levelComp->AddObserver(playerComp);

		return std::move(playerObject);
	}

	void GameLoader::MakeLevelOne()
	{
		const std::string levelOne{ "LevelOne" };
		//SETUP
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", levelOne);
		auto* sceneLvl1 = boop::SceneManager::GetInstance().GetScene(levelOne);
		assert(sceneLvl1);

		//player controls info
		auto howToPlay = std::make_unique<boop::GameObject>();
		howToPlay->AddComponent<boop::TextComponent>(nullptr, "Use D-Pad to move the blue tank, X to inflict damage, A and B to kill a tank")->SetPosition(0,50);
		howToPlay->AddComponent<boop::TextComponent>(nullptr, "Use WASD to move the green tank, C to inflict damage, Z and X to kill a tank")->SetPosition(0,70);
		sceneLvl1->Add(std::move(howToPlay));

		//input player 1 
		auto* player1 = sceneLvl1->FindGameObjectByTag("p1")->GetComponent<Player>();
		assert(player1);
		player1->AddKeyboardMovement(levelOne);

		//set the UI position
		player1->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 200);
		player1->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 250);

		//input player 2
		auto* player2 = sceneLvl1->FindGameObjectByTag("p2")->GetComponent<Player>();
		assert(player2);
		player2->AddControllerMovement(levelOne);
		
		//set the UI position
		player2->GetOwner()->GetComponent<HealthObserver>()->SetPosition(0, 500);
		player2->GetOwner()->GetComponent<ScoreObserver>()->SetPosition(0, 550);
	}

	void GameLoader::MakeMainScreen()
	{
		//SETUP
		const std::string levelName{ "MainScreen" };
		auto& sceneMain = boop::SceneManager::GetInstance().AddScene(levelName);
		
		//selection info
		auto mainMenuText = std::make_unique<boop::GameObject>();
		mainMenuText->AddComponent<boop::TextComponent>(nullptr, "A/SPACE to start")->SetPosition(300,100);
		mainMenuText->AddComponent<boop::TextComponent>(nullptr, "Y/TAB to change")->SetPosition(300,300);

		auto selectionText = std::make_unique<boop::GameObject>();
		selectionText->AddComponent<boop::TextComponent>(nullptr, "Gamemode: SINGLEPLAYER")->SetPosition(300, 330);


		//keyboard commands
		boop::InputManager::GetInstance().AddCommand(levelName, SDL_SCANCODE_SPACE, boop::keyState::isDown,
			std::make_unique<booble::ChangeScene>(mainMenuText.get(), "LevelOne"));
		boop::InputManager::GetInstance().AddCommand(levelName, SDL_SCANCODE_TAB, boop::keyState::isDown,
			std::make_unique<booble::ChangeGamemodeSelection>(selectionText.get(), this));

		sceneMain.Add(std::move(mainMenuText));
		sceneMain.Add(std::move(selectionText));
	}

	void GameLoader::MakeGame()
	{
		//CREATE GAME OBJECTS
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(CreateAir()));
		level::LevelLoader::GetInstance().AssignGameObject(1, std::move(CreateWall(0)));
		level::LevelLoader::GetInstance().AssignGameObject(2, std::move(CreatePlatform(0)));
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(CreatePlayer("GreenTank.png", "p1",200)));
		level::LevelLoader::GetInstance().AssignGameObject(4, std::move(CreatePlayer("BlueTank.png", "p2",400)));

		//Set important tags
		std::vector<std::string> importantTags;
		importantTags.emplace_back("p1");
		importantTags.emplace_back("p2");
		level::LevelLoader::GetInstance().SetImportantTags(importantTags);

		//CREATE LEVELS
		MakeMainScreen();
		MakeLevelOne();

		//LOAD LEVEL
		boop::SceneManager::GetInstance().ChangeScene("MainScreen");
	}

}