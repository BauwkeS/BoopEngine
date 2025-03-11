#pragma once
#include "GameLoader.h"
#include <memory>

#include "GameCommands.h"
#include "../BoopEngine/Boop/Scene/LevelLoader.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/Scene/Scene.h"
#include "../BoopEngine/Boop/GameObject.h"

#include "LevelComponents.h"
#include "player.h"

namespace booble
{
	void GameLoader::MakeGame()
	{
		//CREATE GAME OBJECTS
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(LevelComponents::CreateAir()));
		level::LevelLoader::GetInstance().AssignGameObject(1, std::move(LevelComponents::CreateWall(0)));
		level::LevelLoader::GetInstance().AssignGameObject(2, std::move(LevelComponents::CreatePlatform(0)));
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(LevelComponents::CreatePlayer("GreenTank.png", "p1")));
		level::LevelLoader::GetInstance().AssignGameObject(4, std::move(LevelComponents::CreatePlayer("BlueTank.png", "p2")));

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