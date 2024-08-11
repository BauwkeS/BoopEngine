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
			//std::cout << "you pressing!\n";
			//get player
			//set state if not the same
			//for move -> update the amount times deltatime?
			d;
			//m_pGameObject->SetLocalPosition(100, 100);
			auto playerComp = m_pGameObject->GetComponent<Player>();
			auto currentTest =playerComp->GetStateMachine()->GetActiveState();

			WalkState* walk = dynamic_cast<WalkState*>(currentTest);


			if (walk)
			{
			/*	std::cout << "x pos before: " << m_pGameObject->GetWorldPosition().x << std::endl;
				auto newPos = m_pGameObject->GetWorldPosition();
				newPos.x += m_Speed * d;
				m_pGameObject->SetLocalPosition(newPos);
				std::cout << "x pos AFTER: " << m_pGameObject->GetWorldPosition().x << std::endl;*/
			walk->MoveObject(*playerComp, m_Speed*d);
				return;
			}
			playerComp->GetStateMachine()->GoToState(new WalkState());
			walk->MoveObject(*playerComp, m_Speed * d);
			//std::cout <<"x pos before: " <<  m_pGameObject->GetWorldPosition().x << std::endl;
			//auto newPos = m_pGameObject->GetWorldPosition();
			//newPos.x += m_Speed * d;
			//m_pGameObject->SetLocalPosition(newPos);
			//std::cout <<"x pos AFTER: " <<  m_pGameObject->GetWorldPosition().x << std::endl;

		};

		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;
	};
}