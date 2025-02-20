#include "Player.h"

#include <mutex>

#include "../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../BoopEngine/Boop/Components/Component.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/Scene/Scene.h"


namespace booble
{
	Player::Player(boop::GameObject* owner)
		: Component(owner)
	{
		
		//m_CollisionComp = std::make_unique<boop::CollisionComponent>()
	}

	void Player::FixedUpdate(float)
	{
		//HandleJump(deltaTime);
		AccountCollision();
		/*auto* collision = GetOwner()->GetComponent<boop::CollisionComponent>();
		if (collision) collision->FixedUpdate(deltaTime);*/
	}

	void Player::Update(float deltaTime)
	{
		//m_StateMachine->Update(deltaTime);
		deltaTime;
		
		
	}

	void Player::Render() const
	{
	}

	void Player::AccountCollision()
	{


		//collide with : ENEMY
	}


	//JUUUUUUUUUUUUUMP


	//void Player::StartJump(float strength)
	//{
	//	m_JumpStrength = strength;

	//	if (auto* collision = GetOwner()->GetComponent<boop::CollisionComponent>())
	//	{
	//		collision->ApplyJump(strength);
	//	}
	//	m_JumpRequested = true;
	//}

	//void Player::StopJump()
	//{
	//	m_JumpRequested = false;
	//}

	//void Player::HandleJump(float deltaTime)
	//{
	//	if (m_JumpRequested)
	//	{
	//		auto* collision = GetOwner()->GetComponent<boop::CollisionComponent>();

	//		m_JumpTime += deltaTime;
	//		if (m_JumpTime >= m_MaxJumpTime || collision->IsOnGround())
	//		{
	//			collision->ApplyJump(0);
	//			m_JumpTime = 0.0f;
	//			m_JumpRequested = false;
	//			m_StateMachine->GoToState(new IdleState(*this));
	//		}

	//	}
	//}
}
	