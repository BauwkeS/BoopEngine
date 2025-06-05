#include "Enemy.h"

#include <mutex>

#include "../../BoopEngine/Boop/Components/Component.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../../BoopEngine/Boop/Scene/Scene.h"
#include "../../BoopEngine/Boop/Input/InputManager.h"
#include "../GameCommands.h"
#include "Events.h"
#include "../../BoopEngine/Boop/Event/Subject.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"
#include "HealthObserver.h"
#include "ScoreObserver.h"
#include <glm/geometric.hpp>


Enemy::Enemy(boop::GameObject* owner, int speed, const std::string spritePath)
	: Component(owner)
{
	//add base tank
	m_pTankBase = owner->AddComponent<BaseTank>(speed, spritePath);

}

void Enemy::FixedUpdate()
{
}

void Enemy::Update()
{
	m_pCurrentState->Update();
}

void Enemy::Render() const
{
}

glm::vec2 Enemy::SeePlayer()
{
	auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	auto player1 = scene->FindGameObjectByTag("p1");
	auto player2 = scene->FindGameObjectByTag("p2");

	glm::vec2 resultPos{0,0};

	if (player1 && player2)
	{
		auto tankPos = m_pTankBase->GetOwner()->GetWorldPosition();

		//check player1
		resultPos = CheckPlayerPosSeen(player1->GetWorldPosition());
		//check player2
		if (resultPos == glm::vec2{0,0}) resultPos = CheckPlayerPosSeen(player2->GetWorldPosition());

		////check player 1
		//auto player1Pos = player1->GetWorldPosition();

		////x check
		//if (player1Pos.x - 15 < tankPos.x && player1Pos.x + 15 > tankPos.x) return player1Pos;
		////y check
		//if (player1Pos.y - 15 < tankPos.y && player1Pos.y + 15 > tankPos.y) return player1Pos;


		////check player 2
		//auto player2Pos = player2->GetWorldPosition();
		////x check
		//if (player2Pos.x - 15 < tankPos.x && player2Pos.x + 15 > tankPos.x) return player2Pos;
		////y check
		//if (player2Pos.y - 15 < tankPos.y && player2Pos.y + 15 > tankPos.y) return player2Pos;

	}
	else {
		//no second player, just go to player 1
		float distanceToPlayer1 = glm::distance(m_pTankBase->GetOwner()->GetWorldPosition(), player1->GetWorldPosition());

		if (distanceToPlayer1 < 100.f)
		{
			std::cout << "PLayer1x: " << roundf(player1->GetWorldPosition().x) << " Player1y: " << roundf(player1->GetWorldPosition().y) << std::endl;
			std::cout << "enemyx: " << m_pTankBase->GetOwner()->GetWorldPosition().x << " enemyy: " << m_pTankBase->GetOwner()->GetWorldPosition().y << std::endl;

		}
	}

	return glm::vec2{0,0};
}

glm::vec2 Enemy::CheckPlayerPosSeen(glm::vec2 playerPos)
{
	auto tankPos = m_pTankBase->GetOwner()->GetWorldPosition();

	//x check
	if (playerPos.x - 15 < tankPos.x && playerPos.x + 15 > tankPos.x) return playerPos;
	//y check
	if (playerPos.y - 15 < tankPos.y && playerPos.y + 15 > tankPos.y) return playerPos;

	return glm::vec2{ 0,0 }; //not seen
}

void enemy::GoToClosestPlayer::OnEnter()
{
}
void enemy::GoToClosestPlayer::OnExit()
{
}
enemy::GoToClosestPlayer::GoToClosestPlayer(Enemy* owner)
	: BaseState(owner)
{
}
void enemy::GoToClosestPlayer::Update()
{
	m_pOwner->SeePlayer();

	//auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	//auto player1 = scene->FindGameObjectByTag("p1");
	//auto player2 = scene->FindGameObjectByTag("p2");
//	if (player1 && player2)
//	{
//		// Calculate distances to both players
//		float distanceToPlayer1 = glm::distance(m_pTankBase->GetOwner()->GetWorldPosition(), player1->GetWorldPosition());
//		float distanceToPlayer2 = glm::distance(m_pTankBase->GetOwner()->GetWorldPosition(), player2->GetWorldPosition());
//		// Determine which player is closer
//	/*	if (distanceToPlayer1 < distanceToPlayer2)
//		{
//			m_pTankBase->MoveTowards(player1->GetWorldPosition());
//		}
//		else
//		{
//			m_pTankBase->MoveTowards(player2->GetWorldPosition());
//		}*/
//
//		if (distanceToPlayer1 < 100.f || distanceToPlayer2 < 100.f)
//		{
//			std::cout << "Close to player within 100.f" << std::endl;
//		}
//	}
//	else {
//		//no second player, just go to player 1
//		float distanceToPlayer1 = glm::distance(m_pTankBase->GetOwner()->GetWorldPosition(), player1->GetWorldPosition());
//
//		if (distanceToPlayer1 < 100.f)
//		{
//			std::cout << "Close to player within 100.f" << std::endl;
//		}
//	}
//}
	//}
}