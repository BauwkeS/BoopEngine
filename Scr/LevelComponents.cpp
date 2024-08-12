#include "LevelComponents.h"

#include "GameCommands.h"
#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../BoopEngine/Boop/Components/CollisionComponent.h"
#include "../BoopEngine/Boop/Input/InputManager.h"
#include "Player.h"
#include "../BoopEngine/Boop/Components/PhysicsComponent.h"

namespace booble
{
	std::unique_ptr<boop::GameObject> LevelComponents::CreateAir()
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "", 4.f)));
		return std::move(gameObjPtr);
	}
	std::unique_ptr<boop::GameObject> booble::LevelComponents::CreateWall(int whichBlock)
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		if (whichBlock == 0) {
			gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "purpleBlock.png", 4.f)));
		}
		else {
			gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "stoneBlock.png", 4.f)));
		}
		gameObjPtr->AddComponent(std::move(std::make_unique<boop::CollisionComponent>(nullptr,
			gameObjPtr->GetComponent<boop::TextureComponent>()->GetTextureRect())));
		gameObjPtr->SetTag("Wall");

		return std::move(gameObjPtr);
	}

	std::unique_ptr<boop::GameObject> booble::LevelComponents::CreatePlatform(int whichBlock)
	{
		auto gameObjPtr = std::make_unique<boop::GameObject>();
		if (whichBlock == 0) {
			gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "purpleBlock.png", 4.f)));
		}
		else {
			gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "stoneBlock.png", 4.f)));
		}

		gameObjPtr->AddComponent(std::move(std::make_unique<boop::CollisionComponent>(nullptr,
			gameObjPtr->GetComponent<boop::TextureComponent>()->GetTextureRect())));
		gameObjPtr->SetTag("Platform");

		return std::move(gameObjPtr);
	}

	std::unique_ptr<boop::GameObject> booble::LevelComponents::CreatePlayer()
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		playerObject->AddComponent(std::move(std::make_unique< boop::SpriteComponent>(nullptr, static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4.f)));
		playerObject->AddComponent(std::move(std::make_unique<Player>(nullptr)));
		playerObject->AddComponent(std::move(std::make_unique<boop::CollisionComponent>(nullptr,
			playerObject->GetComponent<boop::SpriteComponent>()->GetTextureRect())));
		playerObject->AddComponent(std::move(std::make_unique<boop::PhysicsComponent>(nullptr)));

		playerObject->SetTag("Player");

		return std::move(playerObject);
	}
}
