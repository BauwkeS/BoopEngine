//#include "Physics.h"
//#include "../BoopEngine/Boop/Components/Component.h"
//
//namespace booble
//{
//	Physics::Physics(SDL_Rect rect)
//		: m_CollisionRect{ rect }
//	{
//	}
//	
//	void Physics::SetCollisionRect(SDL_Rect rect)
//	{
//		m_CollisionRect = rect;
//	}
//
//	SDL_Rect Physics::GetCollisionRect() const
//	{
//		return m_CollisionRect;
//	}
//	boop::Component* Physics::CheckCollision() const
//	{
//		//TO BE IMPROVED:
//		//- maybe send back the component so I know what collided
//
//		//How to spot collision
//		//1. Loop through all scene items
//		//2. Check if they have a collision component -> give to sprites
//		//3. Check if collision is not empty
//		//4. if not then check if it overlaps
//		//5. if it overlaps, send back which component
//
//		SDL_bool intersect{};
//
//		//1
//		for (auto& object : boop::SceneManager::GetInstance().GetActiveScene()->GetObjects())
//		{
//			//2
//			auto collComponent = object->GetComponent<>();
//
//			//3
//			auto coll = collComponent->get();
//			if (coll != nullptr)
//			{
//				//4
//				auto otherRect = coll->GetCollisionRect();
//
//				intersect = SDL_IntersectRect(&m_CollisionRect, &otherRect, nullptr);
//			}
//
//			//intersecting
//			if (intersect) return collComponent;
//
//		}
//
//		//not intersecting
//		return nullptr;
//	}
//}
