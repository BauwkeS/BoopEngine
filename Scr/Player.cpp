#include "Player.h"

#include "../BoopEngine/Boop/Input/InputManager.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/Scene/Scene.h"

namespace booble
{
	Player::Player(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows,
		const float frameSec, const int startPicIndex, const int AmountPics, const float scale, boop::Collision* collision)
	{
		m_SpriteComp = std::make_unique<boop::SpriteComponent>(ownerPtr, texture, cols, rows, frameSec, startPicIndex, AmountPics, scale, collision);
	}

	void Player::InitCommands()
	{
		//auto sceneName = boop::SceneManager::GetInstance().GetActiveScene()->GetName();
		//auto& input = boop::InputManager::GetInstance();
		//{
		//	// Start Move
		//	input.AddCommand(sceneName, SDL_SCANCODE_A, boop::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), -playerSpeed));
		//	input.AddCommand(sceneName, SDL_SCANCODE_D, boop::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), playerSpeed));
		//}
		//{
		//	// Move
		//	input.AddCommand(sceneName, SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<dae::WalkCommand>(player.get(), -playerSpeed));
		//	input.AddCommand(sceneName, SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<dae::WalkCommand>(player.get(), playerSpeed));
		//}
		//{
		//	// End Move
		//	input.AddCommand(sceneName, SDL_SCANCODE_A, boop::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
		//	input.AddCommand(sceneName, SDL_SCANCODE_D, boop::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
		//}
	}

}