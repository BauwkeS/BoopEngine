#include "Player.h"

#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"

namespace booble
{
	std::unique_ptr<boop::GameObject> booble::Player::CreatePlayer()
	{
		auto playerObject = std::make_unique<boop::GameObject>();
		playerObject->AddComponent(std::move(std::make_unique< boop::SpriteComponent>(nullptr, static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4.f)));
		return std::move(playerObject);
	}

}
	