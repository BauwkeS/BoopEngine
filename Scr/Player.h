#pragma once
#include <memory>
#include "States.h"


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
		void LateUpdate(float deltaTime) override;
		void Render() const override;


		std::unique_ptr<Component> Clone() const override;

		PlayerStateMachine* GetStateMachine() { return m_StateMachine.get(); }
		//bool GetIsStuck() { return m_IsStuck; }

		void AccountCollision();

		/*void StartJump(float strength);
		void StopJump();*/


		//bool IsOnGround() const { return m_IsGrounded; }
		void HandleJumps(float);
	private:
		std::unique_ptr<PlayerStateMachine> m_StateMachine;
		std::unique_ptr<IdleState> m_IdleState;
		std::unique_ptr<WalkState> m_WalkState;
		//std::unique_ptr<boop::CollisionComponent> m_CollisionComp;
		//bool m_IsStuck{};


		//jumping
	/*	void HandleJump(float deltaTime);
		bool m_JumpRequested{ false };
		float m_JumpStrength{ 10.0f };
		float m_JumpTime{ 0.0f };
		float m_MaxJumpTime{ 0.2f };*/
		//bool m_IsGrounded{ true };
		void CollideWall();
		void CollidePlatform();
	};

}