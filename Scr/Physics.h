//#include <SDL_rect.h>
//#include <memory>
//
//
//space for the collision and gravity for the player and enemy -> SO BOTH!!
//
//namespace boop
//{
//	class Component;
//}
//
//namespace booble
//{
//	class Physics
//	{
//	private:
//		SDL_Rect m_CollisionRect;
//	public:
//		Physics(SDL_Rect rect);
//
//		~Physics() = default;
//		Physics(const Physics& other);
//		Physics(Physics&& other) = delete;
//		Physics& operator=(const Physics& other) = delete;
//		Physics& operator=(Physics&& other) = delete;
//
//		void SetCollisionRect(SDL_Rect rect);
//		SDL_Rect GetCollisionRect() const;
//
//		boop::Component* CheckCollision() const;
//
//		std::unique_ptr<Physics> Clone() {
//			std::unique_ptr<Physics> collClone =
//				std::make_unique<Physics>(this->m_CollisionRect);
//			return std::move(collClone);
//		}
//	};
//}