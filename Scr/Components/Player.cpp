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

		//add health UI
		auto healthObs = owner->AddComponent<HealthObserver>();
		owner->GetComponent<Health>()->GetSubject()->AddObserver(healthObs);

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
	
		boop::InputManager::GetInstance().AddCommand(sceneName, SDL_SCANCODE_L, boop::keyState::isDown, std::make_unique<booble::ChangeScene>(GetOwner(), "level1_0"));
	}
	void Player::AddControllerMovement(const std::string& sceneName)
	{
		//MOVE
		//move vectors -> this might have to be moved to a better place
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
	}
}
	