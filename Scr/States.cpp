#include "States.h"
#include <iostream>

#include "Player.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"

namespace boop
{
	class SpriteComponent;
}

namespace booble
{
	WalkState::WalkState(boop::Component& gameObj, float speed)
		: BaseState(),
		m_GameObj{gameObj},
		m_Speed{speed}
	{
		if (m_Speed < 0) m_ToTheLeft = true;
		else m_ToTheLeft = false;
	}

	void WalkState::Update(float deltaTime)
	{
		//Update player:
		Player* player = dynamic_cast<Player*>(&m_GameObj);

		if (player)
		{
			//get the world positions and then add 
			boop::GameObject* gameObject = m_GameObj.GetOwner();

			if (gameObject) {
				glm::vec3 newPosition = gameObject->GetWorldPosition();
				newPosition.x += m_Speed * deltaTime;

				gameObject->SetLocalPosition(newPosition);

				player->AccountCollision();
			}
		}


	}


	void WalkState::OnEnter()
	{
		//set correct texure
		//std::cout << "ENTER STATE WALK\n";
		m_GameObj.GetOwner()->GetComponent<boop::SpriteComponent>()->GetTexture()->ChangeTextureVars(7, 6, 7, !(m_Speed < 0));
	}

	void WalkState::OnExit()
	{
		//std::cout << "EXIT STATE\n";
	}

	/*void PlayerStateMachine::Update(float deltaTime)
	{
		m_pState->Update(deltaTime);
	}*/
}
