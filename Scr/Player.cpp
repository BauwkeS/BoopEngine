#include "Player.h"
#include "../BoopEngine/Boop/Components/CollisionComponent.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"


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
		deltaTime;
		AccountCollision();
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
			std::cout << "JAAAAA\n";

			//m_StateMachine->GoToState(new IdleState());

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
		else {
		
			std::cout << "NAAAAAA\n";
		}
		//collide with : PLATFORM


		//collide with : ENEMY
	}
}
	