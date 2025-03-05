#include "LevelComponents.h"

#include "GameCommands.h"
#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../BoopEngine/Boop/Input/InputManager.h"
#include "Player.h"

namespace booble
{
	std::unique_ptr<boop::GameObject> LevelComponents::CreateAir()
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent< boop::TextureComponent>(nullptr, "", 4.f);
		return std::move(gameObjPtr);
	}
	std::unique_ptr<boop::GameObject> booble::LevelComponents::CreateWall(int whichBlock)
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

	std::unique_ptr<boop::GameObject> booble::LevelComponents::CreatePlatform(int whichBlock)
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

	std::unique_ptr<boop::GameObject> booble::LevelComponents::CreatePlayer(const std::string spritePath, const std::string tagName)
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		//playerObject->AddComponent< boop::SpriteComponent>(nullptr, static_cast<std::string>(spritePath), 6, 5, 0.2f, 0, 2, 4.f);
		playerObject->AddComponent< boop::TextureComponent>(nullptr, static_cast<std::string>(spritePath));
		playerObject->AddComponent<Player>(nullptr);
		//playerObject->AddComponent(std::move(std::make_unique<boop::PhysicsComponent>(nullptr)));
		playerObject->SetTag(tagName);

		return std::move(playerObject);
	}
}
