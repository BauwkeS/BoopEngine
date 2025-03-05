#pragma once
#include <memory>
#include "../BoopEngine/Boop/GameObject.h"
#include <glm/vec2.hpp>

namespace boop {
	class GameObject;
	class CollisionComponent;
	class Component;
}

namespace booble
{
	class Player : public boop::Component
	{
	public:
		Player(boop::GameObject* owner);


		void FixedUpdate(float deltaTime) override;
		void Update(float deltaTime) override;
		void Render() const override;

		//bool GetIsStuck() { return m_IsStuck; }

		void AccountCollision();

		//Walk
		void Walk(glm::vec2 speed);

		/*void StartJump(float strength);
		void StopJump();*/


		//bool IsOnGround() const { return m_IsGrounded; }
	private:
		//std::unique_ptr<boop::CollisionComponent> m_CollisionComp;
		//bool m_IsStuck{};

		//float m_Speed{ 0.0f };

		//jumping
	/*	void HandleJump(float deltaTime);
		bool m_JumpRequested{ false };
		float m_JumpStrength{ 10.0f };
		float m_JumpTime{ 0.0f };
		float m_MaxJumpTime{ 0.2f };*/
	};

}