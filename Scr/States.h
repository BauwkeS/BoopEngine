#pragma once
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/States.h"
#include "glm/vec2.hpp"

namespace booble
{
	//STATES EVERYONE HAS
	class IdleState : public boop::BaseState
	{
	public:
		IdleState(boop::Component& gameObj);
		~IdleState() = default;

		void Update(float deltaTime) override { deltaTime; };
		//	void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override{};
	private:
		boop::Component& m_GameObj;
	};
	class WalkState : public boop::BaseState
	{
	public:
		WalkState(boop::Component& gameObj, float Speed, bool jump=false);
		~WalkState() = default;

		void Update(float deltaTime) override;
	//	void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override;

		bool IsGoingToTheLeft() { return m_ToTheLeft; }
		float GetSpeed() { return m_Speed; }
	private:
		boop::Component& m_GameObj;
		float m_Speed{};
		bool m_ToTheLeft{};
		bool m_Jump{};
	};

	class JumpState : public boop::BaseState
	{
	public:
		JumpState(boop::Component& gameObj);
		~JumpState() = default;

		void Update(float) override{};
		//	void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override;
	private:
		boop::Component& m_GameObj;
	};

	class AttackState : public boop::BaseState
	{
	public:
		AttackState() = default;
		~AttackState() = default;

		void Update(float deltaTime) override;
	//	void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override;
	};

	class HurtState : public boop::BaseState
	{
	public:
		HurtState() = default;
		~HurtState() = default;

		void Update(float deltaTime) override;
	//	void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override;
	};



	//PLAYER STATE INFORMATION
	class PlayerStateMachine : public boop::StateMachine
	{
	public:
		PlayerStateMachine(boop::GameObject* owner, boop::BaseState* state)
			: StateMachine(owner, state) {}

		//void Update(float deltaTime) override;
		boop::BaseState* GetActiveState() { return m_pState; }
	private:

	};

	//PLAYER STATE INFORMATION
	//class EnemyStateMachine : public  boop::StateMachine
	//{
	//public:
	//	EnemyStateMachine(boop::BaseState* state, boop::Component* comp);
	//private:
	//	boop::BaseState* m_pState{};
	//};

}