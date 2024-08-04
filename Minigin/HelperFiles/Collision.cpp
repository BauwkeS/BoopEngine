#include "Collision.h"

#include "Scene.h"
#include "SceneManager.h"
#include "Components/SpriteComponent.h"

namespace boop
{
	Collision::Collision(SDL_Rect rect)
		: m_CollisionRect{rect}
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

	bool Collision::CheckCollision() const
	{
		//TO BE IMPROVED:
		//- maybe send back the component so I know what collided

		//How to spot collision
		//1. Loop through all scene items
		//2. Check if they have a collision component -> give to sprites
		//3. Check if collision is not empty
		//4. if not then check if it overlaps
		// return result

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
		}
		return intersect;
	}
}
