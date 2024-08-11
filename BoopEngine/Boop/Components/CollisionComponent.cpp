#include "CollisionComponent.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"

namespace boop
{
	CollisionComponent::CollisionComponent(boop::GameObject* const ownerPtr)
		: Component(ownerPtr),
		m_CollisionRect{0,0,0,0}
	{
	}

	CollisionComponent::CollisionComponent(boop::GameObject* const ownerPtr, SDL_Rect rect)
		: Component(ownerPtr),
		m_CollisionRect{ rect}
	{
	}

	boop::GameObject* CollisionComponent::CheckCollision(const std::string& tag) const
	{
		//TO BE IMPROVED:
		//- maybe send back the component so I know what collided

		//How to spot collision
		//1. Loop through all scene items
		//2. Check if they have a collision component -> give to sprites
		//3. Check if collision is not empty
		//4. if not then check if it overlaps
		//5. if it overlaps, send back which component

		SDL_bool intersect{};

		//1
		//for (auto& object : checkCollidingGO)
		for (auto& object : boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag(tag))
		{
			//2
			auto collComponent = object->GetComponent<CollisionComponent>();

			//3
			//auto coll = collComponent->GetCollisionRect();
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
}
