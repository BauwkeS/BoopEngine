#include "Collision.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Components/SpriteComponent.h"
#include "../Components/Component.h"

namespace boop
{
	Collision::Collision(SDL_Rect rect)
		: m_CollisionRect{rect}
	{
	}

	Collision::Collision(const Collision& other)
		: m_CollisionRect(other.m_CollisionRect)
	{
	}

	void Collision::SetCollisionRect(SDL_Rect rect)
	{
		m_CollisionRect = rect;
	}

	SDL_Rect Collision::GetCollisionRect() const
	{
		return m_CollisionRect;
	}

	Component* Collision::CheckCollision() const
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
		for(auto& object : boop::SceneManager::GetInstance().GetActiveScene()->GetObjects())
		{
			//2
			auto collComponent = object->GetComponent<SpriteComponent>();

			//3
			auto coll = collComponent->GetCollision();
			if (coll != nullptr)
			{
				//4
				auto otherRect = coll->GetCollisionRect();

				intersect = SDL_IntersectRect(&m_CollisionRect, &otherRect, nullptr);
			}

			//intersecting
			if (intersect) return collComponent;

		}
			
		//not intersecting
		return nullptr;
	}
}
