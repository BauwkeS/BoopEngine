#include "Player.h"

#include <mutex>

#include "../../BoopEngine/Boop/Components/Component.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../../BoopEngine/Boop/Scene/Scene.h"
#include "../../BoopEngine/Boop/Input/InputManager.h"
#include "../GameCommands.h"
#include "Events.h"
#include "../../BoopEngine/Boop/Event/Subject.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"
#include "HealthObserver.h"
#include "ScoreObserver.h"


namespace booble
{
	Player::Player(boop::GameObject* owner, int speed, const std::string spritePath)
		: Component(owner), Observer(), m_Subject{ std::make_unique<boop::Subject>() }
	{
		//add base tank
		m_pTankBase = owner->AddComponent<BaseTank>(speed, spritePath);

		//add sprite
		//owner->AddComponent< boop::TextureComponent>(static_cast<std::string>(spritePath));
		//m_Size = sprite->GetSize();

		////add health
		//auto healthComp = owner->AddComponent<Health>(4);
		//auto healthObs = owner->AddComponent<HealthObserver>();
		//healthComp->GetSubject()->AddObserver(healthObs);

		//add score
		auto scoreObs = owner->AddComponent<ScoreObserver>();
		m_Subject->AddObserver(scoreObs);
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
			m_Subject->NotifyObserver(event);
		}
		if (event.id == boop::make_sdbm_hash("PlayerKillRecognizer")) {
			m_Score += 250;
			m_Subject->NotifyObserver(event);
		}
	}

	/*void Player::ResetPosition()
	{
		GetOwner()->SetLocalPosition(m_StartPos.x, m_StartPos.y);
	}*/

	void Player::AddKeyboardMovement(const std::string& sceneName)
	{
		auto speed = m_pTankBase->GetSpeed();
		const glm::vec2 leftVec{ -speed,0};
		const glm::vec2 rightVec{ speed,0 };
		const glm::vec2 upVec{ 0,-speed };
		const glm::vec2 downVec{ 0,speed };

		//walk
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_A, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), leftVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_D, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), rightVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_W, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), upVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_S, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), downVec));

		////TEST ACTIONS
		//boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_C, boop::keyState::isDown, std::make_unique<TestGetHitCommand>(GetOwner()));
		//boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_Z, boop::keyState::isDown, std::make_unique<TestHitTank>(GetOwner()));
		//boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_X, boop::keyState::isDown, std::make_unique<TestHitRecognizer>(GetOwner()));

	}
	void Player::AddControllerMovement(const std::string& sceneName)
	{
		//MOVE
		//move vectors -> this might have to be moved to a better place
		//const int player2Speed = player2->GetComponent<Player>()->GetSpeed();
		auto speed = m_pTankBase->GetSpeed();
		const glm::vec2 leftVec{ -speed,0 };
		const glm::vec2 rightVec{ speed,0 };
		const glm::vec2 upVec{ 0,-speed };
		const glm::vec2 downVec{ 0,speed };

		int controllerId = boop::InputManager::GetInstance().AddController() -1;
		boop::InputManager::GetInstance().AddCommand(sceneName, controllerId, boop::Controller::ControllerButton::DPadLeft, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), leftVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, controllerId, boop::Controller::ControllerButton::DPadRight, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), rightVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, controllerId, boop::Controller::ControllerButton::DPadUp, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), upVec));
		boop::InputManager::GetInstance().AddCommand(sceneName, controllerId, boop::Controller::ControllerButton::DPadDown, boop::keyState::isPressed, std::make_unique<booble::WalkCommand>(GetOwner(), downVec));

		//TEST ACTIONS
		//boop::InputManager::GetInstance().AddCommand(sceneName, controllerId, boop::Controller::ControllerButton::ButtonX, boop::keyState::isDown, std::make_unique<TestGetHitCommand>(GetOwner()));
		//boop::InputManager::GetInstance().AddCommand(sceneName, controllerId, boop::Controller::ControllerButton::ButtonA, boop::keyState::isDown, std::make_unique<TestHitTank>(GetOwner()));
		//boop::InputManager::GetInstance().AddCommand(sceneName, controllerId, boop::Controller::ControllerButton::ButtonB, boop::keyState::isDown, std::make_unique<TestHitRecognizer>(GetOwner()));

	}
}
	