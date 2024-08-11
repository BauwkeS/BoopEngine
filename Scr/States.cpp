#include "States.h"
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace booble
{

	void WalkState::Update(float deltaTime)
	{
		//m_MovementPower = m_Speed * deltaTime;
		deltaTime;
	}


	void WalkState::OnEnter()
	{
		std::cout << "ENTER STATE WALK\n";
	}

	void WalkState::OnExit()
	{
		std::cout << "EXIT STATE\n";
	}

	void WalkState::MoveObject(boop::Component& gameObj)
	{
		boop::GameObject* gameObject = gameObj.GetOwner();

		if (gameObject) {
			// Calculate new position based on movement logic
			glm::vec3 newPosition = gameObject->GetWorldPosition(); // your logic to calculate the new position
			newPosition.x += 100;
				// Update the position of the gameObject
				gameObject->SetLocalPosition(newPosition);

			// Optional: Log the new position for debugging
			std::cout << "New Position: " << glm::to_string(newPosition) << std::endl;
		}
	}

	void PlayerStateMachine::Update(float deltaTime)
	{
		m_pState->Update(deltaTime);
	}
}
