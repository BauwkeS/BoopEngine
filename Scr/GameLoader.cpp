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

		playerObject->AddComponent< boop::TextureComponent>(nullptr, static_cast<std::string>(spritePath)); //add sprite
		auto playerComp = playerObject->AddComponent<Player>(nullptr, playerSpeed); // add base player comp

		//health
		auto healthComp = playerObject->AddComponent<Health>(nullptr, 4);
		auto healthObs = playerObject->AddComponent<HealthObserver>(nullptr);
		healthObs->SetPosition(0, 200); //TO DO MOVE THIS??? MAGIC NUMBER???
		healthComp->AddObserver(healthObs);

		//score
		auto scoreObs = playerObject->AddComponent<ScoreObserver>(nullptr);
		scoreObs->SetPosition(0, 220); //TO DO MOVE THIS??? MAGIC NUMBER???
		playerComp->AddObserver(scoreObs);

		//level brain
		auto levelComp = playerObject->AddComponent<Level>(nullptr);
		levelComp->AddObserver(playerComp);

		return std::move(playerObject);
	}

	void GameLoader::MakeLevelOne()
	{
		//LOAD
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", m_LevelOne);
		boop::SceneManager::GetInstance().ChangeScene(m_LevelOne);

		//SETUP
		auto scene = boop::SceneManager::GetInstance().GetActiveScene();

		//player controls
		auto howToPlay = std::make_unique<boop::GameObject>();
		howToPlay->AddComponent<boop::TextComponent>(nullptr, "Use D-Pad to move the blue tank, X to inflict damage, A and B to kill a tank")->SetPosition(0,50);
		howToPlay->AddComponent<boop::TextComponent>(nullptr, "Use WASD to move the green tank, C to inflict damage, Z and X to kill a tank")->SetPosition(0,70);
		
		scene->Add(std::move(howToPlay));
	}

	void GameLoader::BindInput()
	{
		//for level 1
		auto* sceneLvl1 = boop::SceneManager::GetInstance().GetScene(m_LevelOne);
		assert(sceneLvl1);

		//input player 1 
		auto* player1 = sceneLvl1->FindGameObjectByTag("p1")->GetComponent<Player>();
		assert(player1);
		player1->AddKeyboardMovement(m_LevelOne);

		//input player 2
		auto* player2 = sceneLvl1->FindGameObjectByTag("p2")->GetComponent<Player>();
		assert(player2);
		player2->AddControllerMovement(m_LevelOne);
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
		MakeLevelOne();

		//make a selection for what game type and make the command input from there
		//INPUT
		BindInput();
	}

}