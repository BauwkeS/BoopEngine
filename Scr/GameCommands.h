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
			//change state of the object
				//set the amount with the speed and in the existing function

				//Player
			//auto playerComp = m_pGameObject->GetComponent<Player>();
			//if (playerComp) {
			//	//playerComp->MoveSprite({ 100,0 });
			//}
			//m_pGameObject->SetLocalPosition(100, 0);

			//WalkState* walk{};
			//playerComp->GetStateMachine()->GoToState(walk);


			//get player
			//set state if not the same
			//for move -> update the amount times deltatime?
			d;
			m_pGameObject->SetLocalPosition(100, 100);
			auto playerComp = m_pGameObject->GetComponent<Player>();
			auto currentTest =playerComp->GetStateMachine()->GetActiveState();
		
			//auto testIdle = new IdleState();
			//auto newState = ;
			//if (std::is_same_v<decltype(newState), decltype(currentTest)>)
			//if (typeid(currentTest) == typeid(testIdle))
			if (WalkState* b = dynamic_cast<WalkState*>(currentTest))
			{
				return;
			}
			playerComp->GetStateMachine()->GoToState(new WalkState());


			std::cout << "you pressing!\n";
		};

		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;
	};
}