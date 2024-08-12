#include "States.h"
#include <iostream>

#include "Player.h"
#include "../BoopEngine/Boop/Components/CollisionComponent.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"

namespace boop
{
	class SpriteComponent;
}

namespace booble
{
	void IdleState::OnEnter()
	{
		std::cout << "ENTER STATE IDLE\n";
		bool flip = m_GameObj.GetOwner()->GetComponent<boop::SpriteComponent>()->GetTexture()->IsTextureFlipped();
		m_GameObj.GetOwner()->GetComponent<boop::SpriteComponent>()->GetTexture()->ChangeTextureVars(6, 5, 2, flip,0,0.4f);
	}

	IdleState::IdleState(boop::Component& gameObj)
		:BaseState(), m_GameObj{ gameObj }

	{

	}

	WalkState::WalkState(boop::Component& gameObj, float speed, bool jump)
		: BaseState(),
		m_GameObj{gameObj},
		m_Speed{speed},
		m_Jump{jump}
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
		std::cout << "ENTER STATE WALK\n";
		m_GameObj.GetOwner()->GetComponent<boop::SpriteComponent>()->GetTexture()->ChangeTextureVars(6, 5, 4, !(m_Speed < 0));
	}

	void WalkState::OnExit()
	{
		//std::cout << "EXIT STATE\n";
	}

	JumpState::JumpState(boop::Component& gameObj, float jumpStrength)
		:BaseState(), m_GameObj{gameObj}, m_JumpStrength(jumpStrength)
	{
	}

	void JumpState::OnEnter()
	{
		std::cout << "ENTER STATE JUMP\n";
		bool flip = m_GameObj.GetOwner()->GetComponent<boop::SpriteComponent>()->GetTexture()->IsTextureFlipped();
		m_GameObj.GetOwner()->GetComponent<boop::SpriteComponent>()->GetTexture()->ChangeTextureVars(6, 5, 4,flip,6);

		auto* collComp = m_GameObj.GetOwner()->GetComponent<boop::CollisionComponent>();
		if (collComp)
		{
			//add your jump here
			if (collComp->IsOnGround()) collComp->ApplyJump(m_JumpStrength);

			//add condition when you return to ground to go back to idle state
			//m_GameObj.GetOwner()->GetComponent<PlayerStateMachine>()->GoToState(new IdleState(m_GameObj));

		}

	}

	void JumpState::OnExit()
	{
		m_JumpInitiated = false;
	}

	/*void PlayerStateMachine::Update(float deltaTime)
	{
		m_pState->Update(deltaTime);
	}*/
}
