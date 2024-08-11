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

		//PLAYER
		auto playerObject = LevelComponents::CreatePlayer();
//		auto* playerPtr = playerObject.get(); // Save the raw pointer to find later
		playerObject->SetTag("Player");
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(playerObject));


		//LOAD
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo");
		boop::SceneManager::GetInstance().ChangeScene("Demo");

		//AND INPUTS
		//boop::SceneManager::GetInstance().GetActiveScene()->GetObjects().

		 // Retrieve the scene and find the player object by its pointer
		auto* activeScene = boop::SceneManager::GetInstance().GetActiveScene();

		if (activeScene)
		{
			std::cout << "Active scene retrieved successfully." << std::endl;
			auto* foundPlayer = activeScene->FindGameObjectByTag("Player");


			if (foundPlayer)
			{
				std::cout << "Player found in scene!" << std::endl;
				// Perform operations on the found player...
			boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(foundPlayer, -5.f));
			boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(foundPlayer, 5.f));
			}
			else
			{
				std::cout << "Player not found in scene!" << std::endl;
			}
		}
		else
		{
			std::cout << "Failed to retrieve active scene." << std::endl;
		}

	}

}