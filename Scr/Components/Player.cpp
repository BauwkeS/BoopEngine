#include "Player.h"

#include <mutex>

#include "../../BoopEngine/Boop/Components/Component.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../../BoopEngine/Boop/Scene/Scene.h"
#include "../../BoopEngine/Boop/Input/InputManager.h"
#include "../GameCommands.h"
#include "Events.h"


namespace booble
{
	Player::Player(boop::GameObject* owner, int speed)
		: Component(owner), Observer(), Subject(), m_Speed{speed}
	{
	}

	void Player::FixedUpdate()
	{
	}

	void Player::Update()
	{

	}

	void Player::Render() const
	{
	}

	void Player::OnNotify(boop::Event event)
	{
		if (event.id == boop::make_sdbm_hash("PlayerKillTank")) {
			m_Score += 100;
			NotifyObserver(event);
		}
		if (event.id == boop::make_sdbm_hash("PlayerKillRecognizer")) {
			m_Score += 250;
			NotifyObserver(event);
		}
	}

	void Player::AddKeyboardMovement(const std::string& sceneName)
	{
		const glm::vec2 leftVec{ -m_Speed,0 };
		const glm::vec2 rightVec{ m_Speed,0 };
		const glm::vec2 upVec{ 0,-m_Speed };
		const glm::vec2 downVec{ 0,m_Speed };

		//walk
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), leftVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), rightVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_W, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), upVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_S, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), downVec));

		////TEST ACTIONS
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_C, boop::keyState::isDown, std::make_unique<TestGetHitCommand>(GetOwner()));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_Z, boop::keyState::isDown, std::make_unique<TestHitTank>(GetOwner()));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_X, boop::keyState::isDown, std::make_unique<TestHitRecognizer>(GetOwner()));

	}
	void Player::AddControllerMovement(const std::string& sceneName)
	{
		//MOVE
		//move vectors -> this might have to be moved to a better place
		//const int player2Speed = player2->GetComponent<Player>()->GetSpeed();
		const glm::vec2 leftVec{ -m_Speed,0 };
		const glm::vec2 rightVec{ m_Speed,0 };
		const glm::vec2 upVec{ 0,-m_Speed };
		const glm::vec2 downVec{ 0,m_Speed };

		boop::InputManager::GetInstance().AddController();
		boop::InputManager::GetInstance().AddCommand(sceneName, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadLeft, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), leftVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadRight, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), rightVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadUp, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), upVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::DPadDown, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), downVec));

		//TEST ACTIONS
		boop::InputManager::GetInstance().AddCommand(sceneName, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::ButtonX, boop::keyState::isDown, std::make_unique<TestGetHitCommand>(GetOwner()));
		boop::InputManager::GetInstance().AddCommand(sceneName, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::ButtonA, boop::keyState::isDown, std::make_unique<TestHitTank>(GetOwner()));
		boop::InputManager::GetInstance().AddCommand(sceneName, static_cast<int>(boop::Controller::ControllerId::First), boop::Controller::ControllerButton::ButtonB, boop::keyState::isDown, std::make_unique<TestHitRecognizer>(GetOwner()));

	}
}
	