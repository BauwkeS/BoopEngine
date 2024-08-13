#include "CollisionComponent.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"

namespace booble
{
	class Player;
}


//to-do: jump should NOT be in here 

namespace boop
{
	CollisionComponent::CollisionComponent(boop::GameObject* const ownerPtr, SDL_Rect rect, bool gravityOn)
		: Component(ownerPtr),
		m_CollisionRect{ rect},
		m_GravityEnabled{gravityOn}
	{
	}

	void CollisionComponent::FixedUpdate(float deltaTime)
	{
		
		if (m_GravityEnabled) {
			HandleVerticalMovement(deltaTime);
		}
	}

	boop::GameObject* CollisionComponent::CheckCollision(const std::string& tag) const
	{
		//How to spot collision
		//1. Loop through all scene items
		//2. Check if they have a collision component -> give to sprites
		//3. Check if collision is not empty
		//4. if not then check if it overlaps
		//5. if it overlaps, send back which component

		SDL_bool intersect{};

		//1
		for (auto& object : boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag(tag))
		{
			//2
			auto collComponent = object->GetComponent<CollisionComponent>();

			//3
			if (collComponent)
			{
				//4
				auto otherRect = collComponent->GetCollisionRect();
				auto otherPos = collComponent->GetOwner()->GetWorldPosition();
				otherRect.x = static_cast<int>(otherPos.x);
				otherRect.y = static_cast<int>(otherPos.y);

				auto ownPos = GetOwner()->GetWorldPosition();
				SDL_Rect ownRect = { static_cast<int>(ownPos.x),
					static_cast<int>(ownPos.y),
					m_CollisionRect.w, m_CollisionRect.h };

				intersect = SDL_HasIntersection(&ownRect, &otherRect);
			}

			//intersecting
			if (intersect == SDL_TRUE) {
				return collComponent->GetOwner();
			}
		}

		//not intersecting
		return nullptr;
	}

    void CollisionComponent::ApplyJump(float jumpStrength)
    {
            m_VerticalVelocity = jumpStrength;
            m_IsGrounded = false;
			m_IsJumping=true;
    }

    void CollisionComponent::HandleVerticalMovement(float deltaTime)
    {
        if (!m_IsGrounded && !m_IsJumping)
        {
            m_VerticalVelocity = -300.0f; // Apply a constant fall speed
        }


        auto owner = GetOwner();
        auto position = owner->GetWorldPosition();
        position.y -= m_VerticalVelocity * (deltaTime*2);

        owner->SetLocalPosition(position);
    }

    bool CollisionComponent::HandleJump(float deltaTime)
    {
		if(m_IsJumping)
		{
			if (m_AirCounter >= 0.2) {
				//set time in air
				m_IsJumping = false;

				return true;
			}
			m_AirCounter += deltaTime;
		}
		return false;
    }
}
