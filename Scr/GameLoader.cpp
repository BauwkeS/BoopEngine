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
		playerObject->SetTag("Player"); //set tag for input
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(playerObject));


		std::vector<std::string> tags;
		tags.emplace_back("Player");

		//LOAD
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo",tags);
		boop::SceneManager::GetInstance().ChangeScene("Demo");

		//INPUTS FOR ADDED PLAYER IN SCENE
		if (boop::SceneManager::GetInstance().GetActiveScene())
		{
			auto* foundPlayer = boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("Player");

			if (foundPlayer)
			{
				boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(foundPlayer, -250.f));
				boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(foundPlayer, 250.f));
			}
		}
	}

}