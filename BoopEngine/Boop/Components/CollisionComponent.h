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
		CollisionComponent(boop::GameObject* const ownerPtr, SDL_Rect rect=SDL_Rect{0,0,0,0}, bool gravityOn=false);
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
		bool IsJumping() const { return m_IsJumping; }
		void SetOnGround(bool ground) { m_IsGrounded=ground; }
		void HandleVerticalMovement(float deltaTime);
		void SetGravityEnabled(bool enabled) { m_GravityEnabled = enabled; }
		float GetVerticalVelocity() { return m_VerticalVelocity; }
		void SetVerticalVelocity(float vec) { m_VerticalVelocity = vec; }

		virtual std::unique_ptr<Component> Clone() const override
		{
			// Create a new comp with the same info
			std::unique_ptr<CollisionComponent> collcomp
				= std::make_unique<CollisionComponent>(this->GetOwner()
					,this->m_CollisionRect,this->m_GravityEnabled);
			return std::move(collcomp);
		}

		bool HandleJump(float deltaTime);

	private:
		SDL_Rect m_CollisionRect{};

		// physics
		bool m_GravityEnabled{ false };
		//not everyone needs physics, but I stil which to keep it compacted in here 
		bool m_IsGrounded{ true };
		float m_VerticalVelocity{ 0.0f };

		//jumping things -> SHOULD NOT BE IN THIS COMP
		bool m_IsJumping{ };
		float m_AirCounter{};
		
	};
}

