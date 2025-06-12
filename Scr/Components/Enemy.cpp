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

	m_pTankTexture = GetOwner()->GetComponent<boop::TextureComponent>();
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
	//TODO: Make the follow better -> when stuck behind a wall on the same line -> switch directions too

	auto tankPos = m_pTankBase->GetOwner()->GetWorldPosition();
	auto tankLocalPos = GetOwner()->GetLocalPosition();

	//bool direction{true};
	glm::vec2 newPos{ tankLocalPos };

	//step 1: move x way
	if (m_MovingX && tankPos.x > pos.x) {
		m_MovementVec = glm::vec2{ -m_pTankBase->GetSpeed(),0 };
	}
	else if (m_MovingX && tankPos.x < pos.x)
	{
		m_MovementVec = glm::vec2{ m_pTankBase->GetSpeed(),0 };
	}

	//step 2: move x way
	if (!m_MovingX && tankPos.y > pos.y) {
		m_MovementVec = glm::vec2{ 0, -m_pTankBase->GetSpeed() };
	}
	else if (!m_MovingX && tankPos.y < pos.y)
	{
		m_MovementVec = glm::vec2{ 0, m_pTankBase->GetSpeed()};
	}

	newPos = GetOwner()->GetLocalPosition() + m_MovementVec * boop::DeltaTime::GetInstance().GetDeltaTime();

	
	if (glm::distance(pos.x, newPos.x) < 1 && SeePlayer() != glm::vec2{ 0,0 }) {
		m_MovingX = false;
	}
	else if (glm::distance(pos.y, newPos.y) < 1 && SeePlayer() != glm::vec2{ 0,0 }) {
		m_MovingX = true;
	}
	else if (WouldCollideWithWall(newPos)) {
		newPos.x = static_cast<int>(tankLocalPos.x / 8) * 8.f; //round
		newPos.y = static_cast<int>(tankLocalPos.y / 8) * 8.f; //round
	}

	m_pTankTexture->FlipTextureDir(m_MovementVec);

	GetOwner()->SetLocalPosition(newPos);
}

bool Enemy::WouldCollideWithWall(glm::vec2 newPos)
{
	SDL_Rect checkRect{ static_cast<int>(newPos.x),
			static_cast<int>(newPos.y),
			static_cast<int>(m_pTankBase->GetSize().x),
			static_cast<int>(m_pTankBase->GetSize().y) };

	for (const auto& wall : m_CollisionObjects)
	{
		auto wallPos = wall->GetWorldPosition();
		glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
		SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
			static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };
		

		if (SDL_HasIntersection(&checkRect, &wallRect))
		{
			//collided
			m_MovingX = !m_MovingX;

			return true;
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
	int margin = 5;

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

//------------------------------------------------------------------------

void enemy::GoToClosestPlayer::OnEnter()
{
	
}
void enemy::GoToClosestPlayer::OnExit()
{
	float bulletSpeed = 1.f;

	//look towards the player
	auto tankPos = m_pOwner->GetOwner()->GetWorldPosition();
	int margin = 15;

	auto playerPos = m_pOwner->SeePlayer();

	//y check
	if (playerPos.x - margin < tankPos.x && playerPos.x + margin > tankPos.x)
	{
		if (playerPos.y < tankPos.y) m_pOwner->m_MovementVec = glm::vec2{ 0, -bulletSpeed }; //look up
		else m_pOwner->m_MovementVec = glm::vec2{ 0, bulletSpeed }; //look up
	}
	//x check
	if (playerPos.y - margin < tankPos.y && playerPos.y + margin > tankPos.y) {
		if (playerPos.x < tankPos.x) m_pOwner->m_MovementVec = glm::vec2{ -bulletSpeed,0 }; //look up
		else m_pOwner->m_MovementVec = glm::vec2{ bulletSpeed,0 }; //look up
	}
}
std::unique_ptr<enemy::BaseState> enemy::GoToClosestPlayer::HandleState()
{
	if (m_pOwner->SeePlayer() != glm::vec2{ 0,0 })
	{
		return std::make_unique<enemy::Shoot>(m_pOwner); //change state to shoot
	}
	return nullptr; //no state change
}
enemy::GoToClosestPlayer::GoToClosestPlayer(Enemy* owner)
	: BaseState(owner)
{
}
void enemy::GoToClosestPlayer::Update()
{
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

//------------------------------------------------------------------------


enemy::Shoot::Shoot(Enemy* owner)
	: BaseState(owner)
{
}

void enemy::Shoot::Update()
{
	m_CooldownShoot += boop::DeltaTime::GetInstance().GetDeltaTime();
}

void enemy::Shoot::OnEnter()
{//shoot the bullet
	auto bullet = std::make_unique<boop::GameObject>();
	bullet->SetTag("bullet");
	bullet->AddComponent<Bullet>(m_pOwner->m_MovementVec, m_pOwner->GetPlayer1()->GetChildAt(0)->GetComponent<Level>(), true);
	bullet->AddComponent<boop::TextureComponent>("BulletNPC.png");
	glm::vec2 bulletSpawnPos = m_pOwner->GetOwner()->GetWorldPosition();
	bulletSpawnPos += m_pOwner->GetTankTexture()->GetSize() / 3.f; // Center the bullet spawn position
	bullet->SetLocalPosition(bulletSpawnPos);
	boop::SceneManager::GetInstance().GetActiveScene()->Add(std::move(bullet));
}

void enemy::Shoot::OnExit()
{
	m_CooldownShoot = 0.f; // Reset cooldown
}

std::unique_ptr<enemy::BaseState> enemy::Shoot::HandleState()
{
	if (m_CooldownShoot >= 1.5f) // cooldown time
	{
		return std::make_unique<enemy::GoToClosestPlayer>(m_pOwner); // Change state back to GoToClosestPlayer
	}

	return nullptr;
}

//------------------------------------------------------------------------


enemy::Roam::Roam(Enemy* owner)
	: BaseState(owner)
{
	//m_RandomTargetPos = m_pOwner->GetOwner()->GetWorldPosition();
}

void enemy::Roam::Update()
{
	m_RoamTimer += boop::DeltaTime::GetInstance().GetDeltaTime();

	if (m_RandomTargetPos == glm::vec2{ 0,0 }) FindRandomTargetPos();
	//move to the random target position
	m_pOwner->MoveToPos(m_RandomTargetPos);
	//check if reached the target position
	if (glm::distance(m_pOwner->GetOwner()->GetWorldPosition(), m_RandomTargetPos) < 40.f)
	{
		m_RandomTargetPos = glm::vec2{ 0,0 }; //reset target pos
	}

	if (m_RoamTimer >= 4.f) {
		m_RandomTargetPos = glm::vec2{ 0,0 }; //reset target pos
		m_RoamTimer = 0.f; // Reset roam timer
	}
}

void enemy::Roam::OnEnter()
{
	FindRandomTargetPos();
}

void enemy::Roam::OnExit()
{
	m_RoamTimer = 0.f; // Reset roam timer
}

std::unique_ptr<enemy::BaseState> enemy::Roam::HandleState()
{
	if (m_pOwner->SeePlayer() != glm::vec2{ 0,0 })
	{
		return std::make_unique<enemy::ChasePlayer>(m_pOwner);
	}
	return nullptr; //no state change
}

void enemy::Roam::FindRandomTargetPos()
{
	//roam within a derimeter
	int derimeter = 800;

	//m_RandomTargetPos.x = static_cast<float>(rand() % static_cast<int>(derimeter));
	//m_RandomTargetPos.y = static_cast<float>(rand() % static_cast<int>(derimeter));

	auto tankPos = m_pOwner->GetOwner()->GetWorldPosition();

	while (m_RandomTargetPos.x <= 0 || m_RandomTargetPos.y <= 0 ||
		m_pOwner->WouldCollideWithWall(m_RandomTargetPos))
	{
		m_RandomTargetPos.x = tankPos.x + (static_cast<float>(rand() % static_cast<int>(derimeter))-derimeter/2);
		m_RandomTargetPos.y = tankPos.y + (static_cast<float>(rand() % static_cast<int>(derimeter))-derimeter / 2);
	}
}

//------------------------------------------------------------------------

enemy::ChasePlayer::ChasePlayer(Enemy* owner)
	: BaseState(owner)
{
}

void enemy::ChasePlayer::Update()
{
	m_pOwner->MoveToPos(m_TargetPosition);

	if (glm::distance(m_pOwner->GetOwner()->GetWorldPosition(), m_TargetPosition) < 5.f)
	{
		m_TargetPosition = m_pOwner->SeePlayer();
	}
}

void enemy::ChasePlayer::OnEnter()
{
	m_TargetPosition = m_pOwner->SeePlayer();
}

void enemy::ChasePlayer::OnExit()
{
}

std::unique_ptr<enemy::BaseState> enemy::ChasePlayer::HandleState()
{
	if (m_TargetPosition == glm::vec2{ 0,0 })
	{
		return std::make_unique<enemy::Roam>(m_pOwner); // Change state to Roam if no player is seen
	}
	return nullptr;
}
