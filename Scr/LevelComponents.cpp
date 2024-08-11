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
		return std::move(gameObjPtr);
	}

	std::unique_ptr<boop::GameObject> booble::LevelComponents::CreatePlayer()
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		playerObject->AddComponent(std::move(std::make_unique< boop::SpriteComponent>(nullptr, static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4.f)));
		playerObject->AddComponent(std::move(std::make_unique<Player>(nullptr)));


	//	boop::InputManager::GetInstance().AddCommand("Demo", SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(playerObject.get(), 5.f));



		return std::move(playerObject);
	}
}
