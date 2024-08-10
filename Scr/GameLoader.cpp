#include "GameLoader.h"

#include "../BoopEngine/Boop/Scene/LevelLoader.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"

#include "LevelComponents.h"
#include "player.h"

namespace booble
{
	void GameLoader::MakeGame()
	{
		//EMPTY SPACE
		/*auto gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "", 4.f)));
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(gameObjPtr));*/
		level::LevelLoader::GetInstance().AssignGameObject(0, std::move(LevelComponents::CreateAir()));

		//PURPLE WALL
		/*gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "purpleBlock.png", 4.f)));*/
		level::LevelLoader::GetInstance().AssignGameObject(1, std::move(LevelComponents::CreateWall(0)));

		//PLAYER
		//gameObjPtr = std::make_unique<boop::GameObject>();
		//gameObjPtr->AddComponent(std::move(std::make_unique< boop::SpriteComponent>(nullptr, static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4.f)));
		level::LevelLoader::GetInstance().AssignGameObject(3, std::move( Player::CreatePlayer()));


		//LOAD
		level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo");
		boop::SceneManager::GetInstance().ChangeScene("Demo");
	}

}