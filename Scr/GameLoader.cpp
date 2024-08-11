#include "GameLoader.h"
#include <memory>

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
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move(LevelComponents::CreatePlayer()));


		//LOAD
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo");
		boop::SceneManager::GetInstance().ChangeScene("Demo");

		//AND INPUTS
		//boop::SceneManager::GetInstance().GetActiveScene()->GetObjects().
	}

}