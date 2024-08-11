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

	Component* CollisionComponent::CheckCollision() const
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
		for (auto& object : boop::SceneManager::GetInstance().GetActiveScene()->GetObjects())
		{
			//2
			auto collComponent = object->GetComponent<CollisionComponent>();

			//3
			//auto coll = collComponent->GetCollisionRect();
			if (collComponent)
			{
				//4
				auto otherRect = collComponent->GetCollisionRect();

				intersect = SDL_IntersectRect(&m_CollisionRect, &otherRect, nullptr);
			}

			//intersecting
			if (intersect) return collComponent;

		}

		//not intersecting
		return nullptr;
	}
}
