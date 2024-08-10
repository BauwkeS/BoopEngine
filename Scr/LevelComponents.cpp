#include "LevelComponents.h"

#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "../BoopEngine/Boop/GameObject.h"

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
}
