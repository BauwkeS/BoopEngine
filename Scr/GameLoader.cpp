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

	std::unique_ptr<boop::GameObject> GameLoader::CreatePlayerOne(const std::string spritePath, const std::string tagName, float playerSpeed)
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		//playerObject->AddComponent< boop::SpriteComponent>(nullptr, static_cast<std::string>(spritePath), 6, 5, 0.2f, 0, 2, 4.f);
		playerObject->AddComponent< boop::TextureComponent>(nullptr, static_cast<std::string>(spritePath));
		auto playerComp = playerObject->AddComponent<Player>(nullptr,playerSpeed);
		//playerObject->AddComponent(std::move(std::make_unique<boop::PhysicsComponent>(nullptr)));
		playerObject->SetTag(tagName);

		//health
		auto healthComp = playerObject->AddComponent<Health>(nullptr, 4);
		auto healthObs = playerObject->AddComponent<HealthObserver>(nullptr);
		healthObs->SetPosition(0, 200);
		healthComp->AddObserver(healthObs);

		//score
		auto scoreObs = playerObject->AddComponent<ScoreObserver>(nullptr);
		scoreObs->SetPosition(0, 220);

		//damage test input
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, SDL_SCANCODE_C, boop::keyState::isDown, std::make_unique<TestGetHitCommand>(playerObject.get()));
		
		//level brain
		//auto levelBrain = std::make_unique<boop::GameObject>();
		//auto levelBrain = std::make_unique<boop::GameObject>();
		auto levelComp = playerObject->AddComponent<Level>(nullptr);
		//std::make_unique<Level>();
		levelComp->AddObserver(scoreObs);
		levelComp->AddObserver(playerComp);
		//levelBrain->SetTag("Level");
		//levelBrain->SetParent(playerObject.get(), true);
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, SDL_SCANCODE_Z, boop::keyState::isDown, std::make_unique<TestHitTank>(playerObject.get()));
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, SDL_SCANCODE_X, boop::keyState::isDown, std::make_unique<TestHitRecognizer>(playerObject.get()));

		//input player 1
		//walk
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{ -playerSpeed,0 }));
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{ playerSpeed,0 }));
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, SDL_SCANCODE_W, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{ 0,-playerSpeed }));
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, SDL_SCANCODE_S, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{ 0,playerSpeed }));

		return std::move(playerObject);
	}
	
	std::unique_ptr<boop::GameObject> GameLoader::CreatePlayerTwo(const std::string spritePath, const std::string tagName, float playerSpeed)
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		playerObject->AddComponent< boop::TextureComponent>(nullptr, static_cast<std::string>(spritePath));
		playerObject->AddComponent<Player>(nullptr,playerSpeed);
		playerObject->SetTag(tagName);

		//input player 2
		//walk
		boop::InputManager::GetInstance().AddController();
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadLeft, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{ -playerSpeed,0 }));
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadRight, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{ playerSpeed,0 }));
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadUp, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{ 0,-playerSpeed }));
		boop::InputManager::GetInstance().AddCommand(m_LevelOne, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadDown, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), glm::vec2{0,playerSpeed}));


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

	void GameLoader::MakeGame()
	{
		//CREATE GAME OBJECTS
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(CreateAir()));
		level::LevelLoader::GetInstance().AssignGameObject(1, std::move(CreateWall(0)));
		level::LevelLoader::GetInstance().AssignGameObject(2, std::move(CreatePlatform(0)));
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(CreatePlayerOne("GreenTank.png", "p1",200)));
		level::LevelLoader::GetInstance().AssignGameObject(4, std::move(CreatePlayerTwo("BlueTank.png", "p2",400)));

		//Set important tags
		std::vector<std::string> importantTags;
		importantTags.emplace_back("p1");
		importantTags.emplace_back("p2");
		level::LevelLoader::GetInstance().SetImportantTags(importantTags);

		//CREATE LEVELS
		MakeLevelOne();
	}

}