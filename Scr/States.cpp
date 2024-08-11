#include "States.h"
#include <iostream>

namespace booble
{

	void WalkState::Update(float deltaTime)
	{
		//m_MovementPower = m_Speed * deltaTime;
		deltaTime;
	}


	void WalkState::OnEnter()
	{
		std::cout << "ENTER STATE\n";
	}

	void WalkState::OnExit()
	{
		std::cout << "EXIT STATE\n";
	}

	void PlayerStateMachine::Update(float deltaTime)
	{
		m_pState->Update(deltaTime);
	}
}
