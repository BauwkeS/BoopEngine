#include "Player.h"



namespace booble
{
	Player::Player(boop::GameObject* owner)
		: Component(owner)
	{
		m_StateMachine = std::make_unique<PlayerStateMachine>(owner, new IdleState());
	}

	void Player::FixedUpdate(float deltaTime)
	{
		deltaTime;
	}

	void Player::Update(float deltaTime)
	{
		//m_StateMachine->Update(deltaTime);
		deltaTime;
	}

	void Player::LateUpdate(float deltaTime)
	{
		deltaTime;
	}

	void Player::Render() const
	{
	}

	std::unique_ptr<boop::Component> Player::Clone() const
	{
		std::unique_ptr<Player> spriteComponent
			= std::make_unique<Player>(this->GetOwner());
		return std::move(spriteComponent);
	}
}
	