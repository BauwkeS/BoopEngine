#pragma once

#include "../BoopEngine/Boop/Input/Command.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "Player.h"

//COMMANDS HERE


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

		void Execute(float) override {
		//change state of the object
			//set the amount with the speed and in the existing function

			//Player
			auto playerComp = m_pGameObject->GetComponent<Player>();
			WalkState* walk{};
			playerComp->GetStateMachine()->GoToState(walk);
			std::cout << "hello??????????\n";
		};
		 
		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;
	};
}
