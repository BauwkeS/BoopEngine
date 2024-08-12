#include "Player.h"
#include "../BoopEngine/Boop/Components/CollisionComponent.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../BoopEngine/Boop/Components/PhysicsComponent.h"
#include "../BoopEngine/Boop/Components/Component.h"


namespace booble
{
	Player::Player(boop::GameObject* owner)
		: Component(owner)
	{
		m_StateMachine = std::make_unique<PlayerStateMachine>(owner, new IdleState());
		
		//m_CollisionComp = std::make_unique<boop::CollisionComponent>()
	}

	void Player::FixedUpdate(float deltaTime)
	{
		HandleJump(deltaTime);
		AccountCollision();

		auto* physics = GetOwner()->GetComponent<boop::PhysicsComponent>();
		if (physics) physics->FixedUpdate(deltaTime);
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

	void Player::AccountCollision()
	{
		//check if you are colliding with anything
		auto collComp = GetOwner()->GetComponent<boop::CollisionComponent>();

		//collide with : WALL
		auto collWithWall = collComp->CheckCollision("Wall");
		if (collWithWall)
		{
			//this could and SHOULD be improved tbh

			auto wallCollComp = collWithWall->GetComponent<boop::CollisionComponent>();

			auto playerPos = GetOwner()->GetWorldPosition();
			auto wallPos = wallCollComp->GetOwner()->GetWorldPosition();
			auto wallRect = wallCollComp->GetCollisionRect();

			// Directly position the player next to the wall
			if (playerPos.x < wallPos.x)
			{
				// Player is on the left side of the wall, move to the left edge of the wall
				playerPos.x = wallPos.x - collComp->GetCollisionRect().w;
			}
			else if (playerPos.x > wallPos.x)
			{
				// Player is on the right side of the wall, move to the right edge of the wall
				playerPos.x = wallPos.x + wallRect.w;
			}

			// Set the player's position to the adjusted value
			GetOwner()->SetLocalPosition(playerPos);
		}

		//collide with : PLATFORM


		//collide with : ENEMY
	}

	void Player::StartJump(float strength)
	{
		m_JumpStrength = strength;

		if (!m_JumpRequested)
		{
			m_JumpRequested = true;
		}
	}

	void Player::StopJump()
	{
		m_JumpRequested = false;
	}

	void Player::HandleJump(float deltaTime)
	{
		if (m_JumpRequested)
		{
			auto* physicsComp = GetOwner()->GetComponent<boop::PhysicsComponent>();

			if (physicsComp)
			{
				physicsComp->ApplyJump(m_JumpStrength);
			}

			m_JumpTime += deltaTime;
			if (m_JumpTime >= m_MaxJumpTime)
			{
				physicsComp->ApplyJump(0);
				m_JumpRequested = false;
				m_JumpTime = 0.0f;
			}
		}
	}

}
	