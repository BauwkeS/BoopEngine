#include "Player.h"

#include "../BoopEngine/Boop/Input/InputManager.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/Scene/Scene.h"
#include "Commands.h"

namespace booble
{
	boop::GameObject* CreatePlayer();
	Player::Player(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows,
		const float frameSec, const int startPicIndex, const int AmountPics, const float scale, boop::Collision* collision)
		: Component(ownerPtr)
	{
		m_SpriteComp = std::make_unique<boop::SpriteComponent>(ownerPtr, texture, cols, rows, frameSec, startPicIndex, AmountPics, scale, collision);
		//InitCommands();
	}

	void Player::InitCommands()
	{
		auto sceneName = "Demo";
		{
			// Move
			boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<WalkCommand>(GetOwner(), -5.f));
			boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<WalkCommand>(GetOwner(), 5.f));
		}
	}

	boop::GameObject* CreatePlayer()
	{
		//boop::GameObject* pChar{};


		return nullptr;
	}

}