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


Enemy::Enemy(boop::GameObject* owner)
	: Component(owner)
{
	//add base tank
	m_pTankBase = owner->GetComponent<BaseTank>();

	auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	m_Player1 = scene->FindGameObjectByTag("p1");
	m_Player2 = scene->FindGameObjectByTag("p2");

	m_CollisionObjects = scene->FindAllGameObjectByTag("collision");

	//set the initial state
	//m_pCurrentState = std::make_unique<enemy::GoToClosestPlayer>(this);
}

void Enemy::FixedUpdate()
{
}

void Enemy::Update()
{
	if (m_pCurrentState) m_pCurrentState->Update();
	HandleStateChanges();
}

void Enemy::Render() const
{
}

void Enemy::UpdateFromScene()
{
	auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	m_Player1 = scene->FindGameObjectByTag("p1");
	m_Player2 = scene->FindGameObjectByTag("p2");

	m_CollisionObjects = scene->FindAllGameObjectByTag("collision");
}

glm::vec2 Enemy::SeePlayer()
{
	//auto scene = boop::SceneManager::GetInstance().GetActiveScene();
	//auto player1 = scene->FindGameObjectByTag("p1");
	//auto player2 = scene->FindGameObjectByTag("p2");

	glm::vec2 resultPos{0,0};

	//check player1
	resultPos = CheckPlayerPosSeen(m_Player1->GetWorldPosition());
	//check player2
	if (m_Player2 && !m_Player2->ToDelete() && resultPos == glm::vec2{0,0}) resultPos = CheckPlayerPosSeen(m_Player2->GetWorldPosition());

	//debug check
	//if (resultPos != glm::vec2{ 0,0 }) std::cout << "PLAYER SEEN!\n";

	return resultPos;
}

void Enemy::MoveToPos(glm::vec2)
{
	//for (auto& wall : m_Player->GetCollisionObjects())
	//{
	//	auto wallPos = wall->GetWorldPosition();
	//	glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
	//	SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
	//		static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };

	//	m_ObjectSize.x = static_cast<int>(newXPos);
	//	m_ObjectSize.y = static_cast<int>(newYPos);

	//	//check if the rects intersect or not
	//	if (SDL_HasIntersection(&m_ObjectSize, &wallRect))
	//	{
	//		//you have collided!
	//		return;
	//	}
	//}

	////if you are nto colliding with anything, move player
	//m_pGameObject->SetLocalPosition(newXPos, newYPos);

	//m_pPlayerTexture->FlipTextureDir(m_Speed);
}

bool Enemy::CollideWithWall()
{
	for (const auto& wall : m_CollisionObjects)
	{
		auto wallPos = wall->GetWorldPosition();
		glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
		SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
			static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };
		SDL_Rect checkRect{ static_cast<int>(m_pTankBase->GetOwner()->GetWorldPosition().x),
			static_cast<int>(m_pTankBase->GetOwner()->GetWorldPosition().y),
			static_cast<int>(m_pTankBase->GetSize().x),
			static_cast<int>(m_pTankBase->GetSize().y) };

		//wrong -> dont check the tank, check the positions between the player and the tank pls

		if (SDL_HasIntersection(&checkRect, &wallRect))
		{
			return true; //collision detected
		}
	}

	return false;
}

bool Enemy::CheckWallInBetween(glm::vec2 pos, bool horizontal)
{
	int margin = 20;
	auto tankPos = m_pTankBase->GetOwner()->GetWorldPosition();

	SDL_Rect collisionRect{};

	if (horizontal)
	{
		//when checking x collision

		auto distancePlayerToTank = glm::distance(pos.x, tankPos.x);
		if (pos.x < tankPos.x)
		{
			//player is left from the tank
			collisionRect = { static_cast<int>(pos.x), static_cast<int>(tankPos.y), static_cast<int>(distancePlayerToTank), margin };
		}
		else
		{
			//player is right from the tank
			collisionRect = { static_cast<int>(tankPos.x), static_cast<int>(tankPos.y), static_cast<int>(distancePlayerToTank), margin };
		}
	}
	else
	{
		//check y collision
		auto distancePlayerToTank = glm::distance(pos.y, tankPos.y);

		if (pos.y < tankPos.y)
		{
			//player is above the tank
			collisionRect = { static_cast<int>(tankPos.x), static_cast<int>(pos.y), margin, static_cast<int>(distancePlayerToTank) };
		}
		else
		{
			//player is below the tank
			collisionRect = { static_cast<int>(tankPos.x), static_cast<int>(tankPos.y), margin, static_cast<int>(distancePlayerToTank) };
		}
	}

	//check with walls
	for (const auto& wall : m_CollisionObjects)
	{
		auto wallPos = wall->GetWorldPosition();
		glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
		SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
			static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };
		if (SDL_HasIntersection(&collisionRect, &wallRect))
		{
			return true; //collision detected
		}
	}


	return false;
}

glm::vec2 Enemy::CheckPlayerPosSeen(glm::vec2 playerPos)
{
	auto tankPos = m_pTankBase->GetOwner()->GetWorldPosition();
	int margin = 15;

	//TODO also check for wall collision!

	//y check
	if (playerPos.x - margin < tankPos.x && playerPos.x + margin > tankPos.x
		&& !CheckWallInBetween(playerPos, false))
	{
		//check if you dont look through a wall
		return playerPos;
	}
	//x check
	if (playerPos.y - margin < tankPos.y && playerPos.y + margin > tankPos.y
		&& !CheckWallInBetween(playerPos, true)) return playerPos;

	return glm::vec2{ 0,0 }; //not seen
}

void enemy::GoToClosestPlayer::OnEnter()
{
	
}
void enemy::GoToClosestPlayer::OnExit()
{
}
std::unique_ptr<enemy::BaseState> enemy::GoToClosestPlayer::HandleState()
{

	return std::unique_ptr<BaseState>();
}
enemy::GoToClosestPlayer::GoToClosestPlayer(Enemy* owner)
	: BaseState(owner)
{
}
void enemy::GoToClosestPlayer::Update()
{
	if (m_pOwner->SeePlayer() != glm::vec2{ 0,0 }) std::cout << "SEE PLAYER HEREEE (so you should've shot now)\n";

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

glm::vec2 enemy::GoToClosestPlayer::FindPlayer()
{
	if (m_pOwner->GetPlayer1())
	{
		glm::vec2 playerPos = m_pOwner->GetPlayer1()->GetWorldPosition();
		glm::vec2 tankPos = m_pOwner->GetOwner()->GetWorldPosition();
		// Check if the player is within a certain distance
		if (glm::distance(playerPos, tankPos) < 500.f) // Example distance threshold
		{
			return playerPos; // Return the player's position if seen
		}
	}
	return glm::vec2();
}
