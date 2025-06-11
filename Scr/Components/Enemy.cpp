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

void Enemy::MoveToPos(glm::vec2 pos)
{
	auto tankPos = m_pTankBase->GetOwner()->GetWorldPosition();
	auto tankLocalPos = GetOwner()->GetLocalPosition();

	//bool direction{true};
	glm::vec2 newPos{ tankLocalPos };

	//step 1: move x way
	if (m_MovingX && tankPos.x > pos.x) {
		//m_MovementVec = glm::vec2{ -m_pTankBase->GetSpeed(),0 };
		newPos.x = tankLocalPos.x + -m_pTankBase->GetSpeed() * boop::DeltaTime::GetInstance().GetDeltaTime();
	}
	else if (m_MovingX && tankPos.x < pos.x)
	{
		//m_MovementVec = glm::vec2{ m_pTankBase->GetSpeed(),0 };
		newPos.x = tankLocalPos.x + m_pTankBase->GetSpeed() * boop::DeltaTime::GetInstance().GetDeltaTime();
	}

	//step 2: move x way
	if (!m_MovingX && tankPos.y > pos.y) {
		//m_MovementVec = glm::vec2{ -m_pTankBase->GetSpeed(),0 };
		newPos.y = tankLocalPos.y + -m_pTankBase->GetSpeed() * boop::DeltaTime::GetInstance().GetDeltaTime();
	}
	else if (!m_MovingX && tankPos.y < pos.y)
	{
		//m_MovementVec = glm::vec2{ m_pTankBase->GetSpeed(),0 };
		newPos.y = tankLocalPos.y + m_pTankBase->GetSpeed() * boop::DeltaTime::GetInstance().GetDeltaTime();
	}

	

	//if you cannot move one direction anymore, take the other
	if (m_MovingX && glm::distance(pos.x, newPos.x) < 1)
	{
		if (!CheckWallInBetween(tankPos, false)) {

		m_MovingX = false; //change direction to y
		return;
		}
	}
	else if (!m_MovingX && glm::distance(pos.y, newPos.y) < 1)
	{
		if (!CheckWallInBetween(tankPos, true)) {
			m_MovingX = true; //change direction to x
			return;
		}
	}

	newPos = WouldCollideWithWall(newPos);

	//dont collide in a wall, if you would you go the other way on x or y
	//if (WouldCollideWithWall(newPos)) {
	//	m_MovingX = !m_MovingX;
	//	std::cout << "Would collide with wall, changing direction!\n" << "posx: " << newPos.x << " | posy: " << newPos.y << std::endl;;
	//	return; //exit if you would collide with a wall
	//}

	//step 2: move y way
	/*if (!direction && tankPos.y > pos.y) m_MovementVec = glm::vec2{ 0,-m_pTankBase->GetSpeed() };
	else if (!direction && tankPos.y < pos.y) m_MovementVec = glm::vec2{ 0,m_pTankBase->GetSpeed() };

	*/


	//if (pos.x < tankPos.x)
	//{
	//	m_MovementVec.x = -m_pTankBase->GetSpeed();
	//}
	//else if (pos.x > tankPos.x)
	//{
	//	moveVec.x = m_pTankBase->GetSpeed();
	//}
	//if (pos.y < tankPos.y)
	//{
	//	moveVec.y = -m_pTankBase->GetSpeed();
	//}
	//else if (pos.y > tankPos.y)
	//{
	//	moveVec.y = m_pTankBase->GetSpeed();
	//}
	//m_MovementVec = moveVec;
	//m_pTankBase->Move(moveVec);

	//std::cout << "m_MovingX: " << m_MovingX << std::endl;

	GetOwner()->SetLocalPosition(newPos);


	/*GetOwner()->SetLocalPosition(
		GetOwner()->GetLocalPosition().x + m_MovementVec.x * boop::DeltaTime::GetInstance().GetDeltaTime(),
		GetOwner()->GetLocalPosition().y);*/
	//	GetOwner()->GetLocalPosition().y + m_MovementVec.y * boop::DeltaTime::GetInstance().GetDeltaTime());

	//m_pOwner->GetOwner()->SetLocalPosition(m_pOwner->GetOwner()->GetLocalPosition() + m_TargetPosition);
}

glm::vec2 Enemy::WouldCollideWithWall(glm::vec2 newPos)
{
	for (const auto& wall : m_CollisionObjects)
	{
		auto wallPos = wall->GetWorldPosition();
		glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
		SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
			static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };
		SDL_Rect checkRect{ static_cast<int>(newPos.x),
			static_cast<int>(newPos.y),
			static_cast<int>(m_pTankBase->GetSize().x),
			static_cast<int>(m_pTankBase->GetSize().y) };

		if (SDL_HasIntersection(&checkRect, &wallRect))
		{
			//collided
			m_MovingX = !m_MovingX;

			auto testpos = GetOwner()->GetLocalPosition();
			int calcnewTest = static_cast<int>(testpos.x / 8) *8;
			int calcnewTestY = static_cast<int>(testpos.y / 8) *8;

			int newX = static_cast<int>(newPos.x/8);
			int newY = static_cast<int>(newPos.y /8);
			newPos.x = newX * 8.f; //round to 8
			newPos.y = newY * 8.f; //round to 8

			if (static_cast<float>(calcnewTest) != newPos.x || static_cast<float>(calcnewTestY) != newPos.y)
			{
				newPos.x = static_cast<float>(calcnewTest);
				newPos.y = static_cast<float>(calcnewTestY);
			}

			return newPos; //return the new position
		}
	}

	return newPos;
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
	//if (m_pOwner->SeePlayer() != glm::vec2{ 0,0 }) std::cout << "SEE PLAYER HEREEE (so you should've shot now)\n";

	m_pOwner->MoveToPos(FindPlayer());
}

glm::vec2 enemy::GoToClosestPlayer::FindPlayer()
{
	glm::vec2 returnVec{};

	if (m_pOwner->GetPlayer1())
	{
		glm::vec2 playerPos = m_pOwner->GetPlayer1()->GetWorldPosition();
		glm::vec2 tankPos = m_pOwner->GetOwner()->GetWorldPosition();

		float distance{100000000.f};
		

		//check if there is a second player
		if (m_pOwner->GetPlayer2() && !m_pOwner->GetPlayer2()->ToDelete()) {
			distance = glm::distance(m_pOwner->GetPlayer2()->GetWorldPosition(), tankPos);
			returnVec = m_pOwner->GetPlayer2()->GetWorldPosition();
		}

		// Check if the player is within a certain distance
		if (glm::distance(playerPos, tankPos) < distance) // Example distance threshold
		{
			returnVec = playerPos; // Return the player's position if seen
		}
	}
	return returnVec;
}
