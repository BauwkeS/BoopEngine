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

#include "player.h"

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

	std::unique_ptr<boop::GameObject> GameLoader::CreatePlayer(const std::string spritePath, const std::string tagName)
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		//playerObject->AddComponent< boop::SpriteComponent>(nullptr, static_cast<std::string>(spritePath), 6, 5, 0.2f, 0, 2, 4.f);
		playerObject->AddComponent< boop::TextureComponent>(nullptr, static_cast<std::string>(spritePath));
		playerObject->AddComponent<Player>(nullptr);
		//playerObject->AddComponent(std::move(std::make_unique<boop::PhysicsComponent>(nullptr)));
		playerObject->SetTag(tagName);

		return std::move(playerObject);
	}

	void GameLoader::MakeGame()
	{
		//CREATE GAME OBJECTS
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(CreateAir()));
		level::LevelLoader::GetInstance().AssignGameObject(1, std::move(CreateWall(0)));
		level::LevelLoader::GetInstance().AssignGameObject(2, std::move(CreatePlatform(0)));
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(CreatePlayer("GreenTank.png", "p1")));
		level::LevelLoader::GetInstance().AssignGameObject(4, std::move(CreatePlayer("BlueTank.png", "p2")));

		//Set important tags
		std::vector<std::string> importantTags;
		importantTags.emplace_back("Player");

		//LOAD
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo", importantTags);
		boop::SceneManager::GetInstance().ChangeScene("Demo");

		//INPUTS FOR ADDED PLAYER IN SCENE
		if (boop::SceneManager::GetInstance().GetActiveScene())
		{
			auto* player1 = boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("p1");

			//walk
			const float playerspeed1{ 200 };
			boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player1, glm::vec2{ -playerspeed1,0}));
			boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player1, glm::vec2{ playerspeed1,0 }));
			boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_W, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player1, glm::vec2{ 0,-playerspeed1 }));
			boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_S, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player1, glm::vec2{ 0,playerspeed1 }));
		
		
			auto* player2 = boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("p2");
			
			const float playerspeed2{ 400 };
			boop::InputManager::GetInstance().AddController();
			boop::InputManager::GetInstance().AddCommand("Demo", static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadLeft, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player2, glm::vec2{ -playerspeed2,0 }));
			boop::InputManager::GetInstance().AddCommand("Demo", static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadRight, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player2, glm::vec2{ playerspeed2,0 }));
			boop::InputManager::GetInstance().AddCommand("Demo", static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadUp, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player2, glm::vec2{ 0,-playerspeed2 }));
			boop::InputManager::GetInstance().AddCommand("Demo", static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadDown, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(player2, glm::vec2{ 0,playerspeed2 }));
		}
	}

}