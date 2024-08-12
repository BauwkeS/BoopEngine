#pragma once

#include "../BoopEngine/Boop/Input/Command.h"

#include "Player.h"
#include <iostream>

//COMMANDS HERE
namespace boop
{
	class GameObject;
	class Command;
	class SpriteComponent;
}

namespace booble
{
	//MOVEMENT
	class WalkCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
		float m_Speed;
		bool m_Jump;
		float m_JumpForce;
	public:
		WalkCommand(boop::GameObject* component, float speed, bool jump = false, float jumpForce = 0.0f)
			: m_pGameObject{ component }, m_Speed{ speed }, m_Jump{ jump }, m_JumpForce{ jumpForce } {}
		//make sure you can walk without jumping
		~WalkCommand() = default;

		void Execute(float d) override {

			//FOR THE PLAYER
			auto playerComp = m_pGameObject->GetComponent<Player>();
			if (playerComp)
			{
				//check if the current state is walking already
				auto currentState = playerComp->GetStateMachine()->GetActiveState();
				WalkState* walk = dynamic_cast<WalkState*>(currentState);

				//check if the direction is correct
				bool checkGoingLeft = m_Speed < 0;

				if (walk && checkGoingLeft == walk->IsGoingToTheLeft()) walk->Update(d); //if all is good, update it
				else playerComp->GetStateMachine()->GoToState(new WalkState(*playerComp, m_Speed));
				//if not then set it correctly

				//add jumping
				//if (m_Jump) playerComp->Jump(m_JumpForce);
			}


		};

		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;

	};

	class StopWalkingCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
	public:
		StopWalkingCommand(boop::GameObject* component)
			: m_pGameObject{ component } {}
		//make sure you can walk without jumping
		~StopWalkingCommand() = default;

		void Execute(float) override {

			//FOR THE PLAYER
			auto playerComp = m_pGameObject->GetComponent<Player>();
			if (playerComp)
			{
				//check if the current state is walking already
				auto currentState = playerComp->GetStateMachine()->GetActiveState();
				IdleState* idle = dynamic_cast<IdleState*>(currentState);

				if (!idle) playerComp->GetStateMachine()->GoToState(new IdleState(*playerComp));
			}


		};

		StopWalkingCommand(const StopWalkingCommand& other) = delete;
		StopWalkingCommand(StopWalkingCommand&& other) = delete;
		StopWalkingCommand& operator=(const StopWalkingCommand& other) = delete;
		StopWalkingCommand& operator=(StopWalkingCommand&& other) = delete;

	};

	class JumpCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
		float m_JumpStrength;
	public:
		JumpCommand(boop::GameObject* component, float jumpStrength)
			: m_pGameObject{ component }, m_JumpStrength{ jumpStrength } {}

		~JumpCommand() = default;

		void Execute(float) override {
			auto playerComp = m_pGameObject->GetComponent<Player>();
			if (playerComp) {
				playerComp->StartJump(m_JumpStrength);


				// check if the current state is walking already
				auto currentState = playerComp->GetStateMachine()->GetActiveState();
				JumpState* jump = dynamic_cast<JumpState*>(currentState);

				
				if (!jump) playerComp->GetStateMachine()->GoToState(new JumpState(*playerComp));
				//if not then set it correctly

				//add jumping
				//if (m_Jump) playerComp->Jump(m_JumpForce);

			}
		}

		JumpCommand(const JumpCommand& other) = delete;
		JumpCommand(JumpCommand&& other) = delete;
		JumpCommand& operator=(const JumpCommand& other) = delete;
		JumpCommand& operator=(JumpCommand&& other) = delete;
	};
};
