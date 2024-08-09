#pragma once
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/States.h"

namespace booble
{
	//STATES EVERYONE HAS
	class WalkState : public boop::BaseState
	{
	public:
		WalkState() = default;
		~WalkState() = default;

		void Update(float deltaTime) override;
		void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override;
	};

	class AttackState : public boop::BaseState
	{
	public:
		AttackState() = default;
		~AttackState() = default;

		void Update(float deltaTime) override;
		void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override;
	};

	class HurtState : public boop::BaseState
	{
	public:
		HurtState() = default;
		~HurtState() = default;

		void Update(float deltaTime) override;
		void Render(float deltaTime) override;

		void OnEnter() override;
		void OnExit() override;
	};



	//PLAYER STATE INFORMATION
	class PlayerStateMachine : public boop::StateMachine
	{
	public:
		PlayerStateMachine(boop::BaseState* state, boop::Component* comp);
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