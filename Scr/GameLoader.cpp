#include "GameLoader.h"
#include <memory>

#include "GameCommands.h"
#include "../BoopEngine/Boop/Scene/LevelLoader.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/Scene/Scene.h"
#include "../BoopEngine/Boop/GameObject.h"

#include "LevelComponents.h"
#include "player.h"
#include "../TimeEx.h"

namespace booble
{
	void GameLoader::MakeGame()
	{
		//CREATE GAME OBJECTS
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(LevelComponents::CreateAir()));
		level::LevelLoader::GetInstance().AssignGameObject(1, std::move(LevelComponents::CreateWall(0)));
		level::LevelLoader::GetInstance().AssignGameObject(2, std::move(LevelComponents::CreatePlatform(0)));
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(LevelComponents::CreatePlayer()));

		//Set important tags
		std::vector<std::string> importantTags;
		importantTags.emplace_back("Player");

		//LOAD
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo", importantTags);
		boop::SceneManager::GetInstance().ChangeScene("Demo");

		//INPUTS FOR ADDED PLAYER IN SCENE
		if (boop::SceneManager::GetInstance().GetActiveScene())
		{
			auto* foundPlayer = boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("Player");

			if (foundPlayer)
			{
				//foundPlayer->SetToDelete();
			}
		}

		//time ex:
		auto& timeScene = boop::SceneManager::GetInstance().AddScene("time");
		auto timeObj = std::make_unique<boop::GameObject>();
		timeObj->AddComponent<TimeExComp>(nullptr);
		timeScene.Add(std::move(timeObj));
		boop::SceneManager::GetInstance().ChangeScene("time");
	}

}
