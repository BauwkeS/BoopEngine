#include <SDL_rect.h>

namespace boop
{
	class Component;

	class Collision final
	{
	private:
		SDL_Rect m_CollisionRect;
	public:
		Collision(SDL_Rect rect);

		~Collision()=default;
		Collision(const Collision& other);
		Collision(Collision&& other) = delete;
		Collision& operator=(const Collision& other) = delete;
		Collision& operator=(Collision&& other) = delete;

		void SetCollisionRect(SDL_Rect rect);
		SDL_Rect GetCollisionRect() const;

		Component* CheckCollision() const;
	};
}