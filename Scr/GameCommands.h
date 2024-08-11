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
	public:
		WalkCommand(boop::GameObject* component, float speed) : m_pGameObject{ component }, m_Speed{ speed } {};
		~WalkCommand() = default;

		void Execute(float d) override {
			//player
			auto playerComp = m_pGameObject->GetComponent<Player>();

			//check if the current state is walking already
			auto currentState = playerComp->GetStateMachine()->GetActiveState();
			WalkState* walk = dynamic_cast<WalkState*>(currentState);

			//check if the direction is correct
			bool checkGoingLeft = m_Speed < 0;

			if (walk && checkGoingLeft == walk->IsGoingToTheLeft()) walk->Update(d); //if all is good, update it
			else playerComp->GetStateMachine()->GoToState(new WalkState(*playerComp, m_Speed));
			//if not then set it correctly

		};

		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;
	};
}