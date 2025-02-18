#include "Player.h"

#include <mutex>

#include "../BoopEngine/Boop/Components/CollisionComponent.h"
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

	void Player::LateUpdate(float deltaTime)
	{
		deltaTime;
		AccountCollision();
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
		CollideWall();
		CollidePlatform();

		//collide with : ENEMY
	}


	void Player::CollideWall()
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

	void Player::CollidePlatform()
	{
		////check if you are colliding with anything
		auto collComp = GetOwner()->GetComponent<boop::CollisionComponent>();


		//float highestGroundY = std::numeric_limits<float>::lowest();

		//SDL_Rect playerRect = collComp->GetCollisionRect();
		//playerRect.x = static_cast<int>(GetOwner()->GetWorldPosition().x);
		//playerRect.y = static_cast<int>(GetOwner()->GetWorldPosition().y);
		//SDL_Rect paddedRect = playerRect;
		//++paddedRect.h;
		//++paddedRect.w;


		//// Collide with : PLATFORM
		//auto collWithWall = collComp->CheckCollision("Platform");
		//if (collWithWall)
		//{
		//	//this could and SHOULD be improved tbh

		//	auto wallCollComp = collWithWall->GetComponent<boop::CollisionComponent>();

		//	auto playerPos = GetOwner()->GetWorldPosition();
		//	auto platformPos = wallCollComp->GetOwner()->GetWorldPosition();
		//	auto wallRect = wallCollComp->GetCollisionRect();

		//	// Directly position the player next to the wall
		//	if (playerPos.x < platformPos.x)
		//	{
		//		// Player is on the left side of the wall, move to the left edge of the wall
		//		playerPos.x = platformPos.x - collComp->GetCollisionRect().w;
		//	}
		//	else if (playerPos.x > platformPos.x)
		//	{
		//		// Player is on the right side of the wall, move to the right edge of the wall
		//		playerPos.x = platformPos.x + wallRect.w;
		//	}

		//	// Set the player's position to the adjusted value
		//	GetOwner()->SetLocalPosition(playerPos);
		//}

		//-----


		auto collWithPlatform = collComp->CheckCollision("Platform");
		if (collWithPlatform)
		{
			auto platformCollComp = collWithPlatform->GetComponent<boop::CollisionComponent>();

			auto playerPos = GetOwner()->GetWorldPosition();
			auto platformPos = platformCollComp->GetOwner()->GetWorldPosition();
			auto platformRect = platformCollComp->GetCollisionRect();

			auto playerRect = collComp->GetCollisionRect();

			// Check if the player is on top of the platform
			if (playerPos.y + playerRect.h >= platformPos.y &&  // Allow some leeway for float precision
				playerPos.y + playerRect.h <= platformPos.y + 2.0f)
			{
				// Adjust the player's position to sit on top of the platform
				playerPos.y = platformPos.y - playerRect.h;

				// Set the player's position to the adjusted value
				GetOwner()->SetLocalPosition(playerPos);

				// Mark the player as grounded (if needed)
				collComp->SetOnGround(true);
			}
			else
			{
				// If not colliding with the top of the platform, player is not grounded
				collComp->SetOnGround(false);
			}
		}


		//--------------


		//for (const auto& object : boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("Platform"))
		//{
		//	auto* collPlatform = object->GetComponent<boop::CollisionComponent>();
		//	if (!collPlatform) continue;


		//	SDL_Rect otherRect = collPlatform->GetCollisionRect();
		//	auto otherPos = object->GetWorldPosition();
		//	otherRect.x = static_cast<int>(otherPos.x);
		//	otherRect.y = static_cast<int>(otherPos.y);

		//	//bool isFallingOnto = collComp->GetVerticalVelocity() <= 0 && playerRect.y + playerRect.h <= otherRect.y;
		//	bool isIntersecting = SDL_HasIntersection(&paddedRect, &otherRect);

		//	if (isIntersecting && collComp->GetVerticalVelocity() <=0 && otherRect.y > highestGroundY)
		//	{
		//		highestGroundY = static_cast<float>(otherRect.y);
		//		collComp->SetOnGround(true);
		//	}
		//}

		//if (collComp->IsOnGround())
		//{
		//	GetOwner()->SetLocalPosition({ GetOwner()->GetWorldPosition().x, highestGroundY - playerRect.h, 0 });
		//	collComp->SetVerticalVelocity(0);
		//}
		

		//auto wallCollComp = collWithplatform->GetComponent<boop::CollisionComponent>();

			//auto playerPos = GetOwner()->GetWorldPosition();
			//auto wallPos = wallCollComp->GetOwner()->GetWorldPosition();
			//auto wallRect = wallCollComp->GetCollisionRect();

			//// Directly position the player next to the wall
			//if (playerPos.x < wallPos.x)
			//{
			//	// Player is on the left side of the wall, move to the left edge of the wall
			//	playerPos.x = wallPos.x - collComp->GetCollisionRect().w;
			//}
			//else if (playerPos.x > wallPos.x)
			//{
			//	// Player is on the right side of the wall, move to the right edge of the wall
			//	playerPos.x = wallPos.x + wallRect.w;
			//}

			//// Set the player's position to the adjusted value
			//GetOwner()->SetLocalPosition(playerPos);



		//auto collWithPlatform = collComp->CheckCollision("Platform");
		//if (collWithPlatform)
		//{
		//	auto platformCollComp = collWithPlatform->GetComponent<boop::CollisionComponent>();

		//	auto playerPos = GetOwner()->GetWorldPosition();
		//	auto platformPos = platformCollComp->GetOwner()->GetWorldPosition();
		//	auto platformRect = platformCollComp->GetCollisionRect();

		//	auto playerRect = collComp->GetCollisionRect();

		//	// Check if the player is on top of the platform
		//	if (playerPos.y + playerRect.h <= platformPos.y + 5.0f &&  // Allow some leeway for float precision
		//		playerPos.y + playerRect.h >= platformPos.y &&          // Check if the bottom of the player is on the platform
		//		playerPos.x + playerRect.w > platformPos.x &&           // Check if the player is within the platform's width
		//		playerPos.x < platformPos.x + platformRect.w)
		//	{
		//		// Adjust the player's position to sit on top of the platform
		//		playerPos.y = platformPos.y - playerRect.h;

		//		// Set the player's position to the adjusted value
		//		GetOwner()->SetLocalPosition(playerPos);

		//		// Mark the player as grounded (if needed)
		//		collComp->SetOnGround(true);
		//	}
		//	else
		//	{
		//		// If not colliding with the top of the platform, player is not grounded
		//		collComp->SetOnGround(false);
		//	}
		//}
	}
}
	