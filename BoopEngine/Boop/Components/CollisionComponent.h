#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "SDL_rect.h"

namespace boop
{
	class CollisionComponent : public Component
	{
	public:
		CollisionComponent(boop::GameObject* const ownerPtr);
		CollisionComponent(boop::GameObject* const ownerPtr, SDL_Rect rect);
		~CollisionComponent() override{};

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override;
		void LateUpdate(float deltaTime) override { deltaTime = 1; }
		void Update(float deltaTime) override { deltaTime; };
		void Render() const override {};

		void SetCollisionRect(SDL_Rect rect) { m_CollisionRect = rect; }
		SDL_Rect GetCollisionRect() const { return m_CollisionRect; };

		//checks
		boop::GameObject* CheckCollision(const std::string& tag) const;

		// physics
		void ApplyJump(float jumpStrength);
		bool IsOnGround() const { return m_IsGrounded; }
		void HandleVerticalMovement(float deltaTime);


		virtual std::unique_ptr<Component> Clone() const override
		{
			// Create a new comp with the same info
			std::unique_ptr<CollisionComponent> collcomp
				= std::make_unique<CollisionComponent>(this->GetOwner()
					,this->m_CollisionRect);
			return std::move(collcomp);
		}

	private:
		//std::unique_ptr<Collision> m_pCollision;
		SDL_Rect m_CollisionRect{};

		// physics
		bool m_IsGrounded{ true };
		float m_VerticalVelocity{ 0.0f };
		void CheckGroundCollision();
	};
}

