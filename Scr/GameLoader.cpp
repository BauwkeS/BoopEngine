#include "GameLoader.h"

#include "../BoopEngine/Boop/Scene/LevelLoader.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"

namespace booble
{
	void GameLoader::MakeGame()
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "", 4.f)));
		level::LevelLoader::GetInstance().AssignGameObject(0, gameObjPtr.get());

		gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "purpleBlock.png", 4.f)));
		level::LevelLoader::GetInstance().AssignGameObject(1, gameObjPtr.get());

		gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent(std::move(std::make_unique< boop::SpriteComponent>(nullptr, static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4.f)));
		level::LevelLoader::GetInstance().AssignGameObject(3, gameObjPtr.get());

		level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo");

		boop::SceneManager::GetInstance().ChangeScene("Demo");
	}

}