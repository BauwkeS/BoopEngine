#pragma once
#include "Level.h"
#include "Components/Events.h"
#include "../BoopEngine/Boop/Event/Event.h"
#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "GameLoader.h"

#include "Components/Player.h"
#include "Components/Health.h"

Level::Level(boop::GameObject* owner) : Component(owner),
m_Subject{ std::make_unique<boop::Subject>() }
{
	//add player
	//auto playerComp = owner->GetParent()->GetComponent<booble::Player>();
	//m_Subject->AddObserver(playerComp);
}

void Level::FixedUpdate()
{
	//check for collisions of the bullets and tanks

	if (!m_BaseTank) return;

	auto playerPos = GetOwner()->GetWorldPosition();
	glm::vec2 playerSize = m_BaseTank->GetSize();

	SDL_Rect playerRect{ static_cast<int>(playerPos.x), static_cast<int>(playerPos.y),
		static_cast<int>(playerSize.x), static_cast<int>(playerSize.y) };


	CollideWithTank(playerRect);
	CollideWithDiamond(playerRect);
}

void Level::ResetPlayerCollision(boop::Scene* scene)
{
	m_CollisionObjects.clear();
	m_Enemies.clear();

	//load up the vectors with the information about the scene yuo're in
	m_CollisionObjects = scene->FindAllGameObjectByTag("collision");

	//get player info
	//auto playerInfo = pScene->FindGameObjectByTag("p1");
	auto playerComp = GetOwner()->GetParent()->GetComponent<BaseTank>();
	playerComp->SetStartPos(GetOwner()->GetWorldPosition());
	if (playerComp) m_BaseTank = playerComp;
	
	//get enemy info
	auto enemyInfo = scene->FindAllGameObjectByTag("enemy");
	for (auto& enemy : enemyInfo)
	{
		auto enemyComp = enemy->GetComponent<Enemy>();
		if (enemyComp)
		{
			enemyComp->GetTankBase()->SetStartPos(enemy->GetWorldPosition());
			m_Enemies.emplace_back(enemyComp);
		}
	}
	//get diamond info
	m_Diamond = scene->FindGameObjectByTag("diamond")->GetComponent<boop::TextureComponent>();
}

void Level::CollideWithBullet()
{
	m_BaseTank->GetOwner()->GetComponent<Health>()->TakeDamage();
	m_BaseTank->ResetPosition();
	for (auto& enemy : m_Enemies)
	{
		enemy->GetTankBase()->ResetPosition();
	}
}

void Level::CollideWithTank(SDL_Rect playerRect)
{
	
	//check if player runs in with another tank
	for (auto& enemy : m_Enemies)
	{
		if (!enemy || enemy->GetOwner()->IsGhost()) continue;
		auto enemyPos = enemy->GetOwner()->GetWorldPosition();
		glm::vec2 enemySize = enemy->GetTankBase()->GetSize();

		SDL_Rect enemyRect{ static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y),
			static_cast<int>(enemySize.x), static_cast<int>(enemySize.y) };

		//check if the rects intersect or not
		if (SDL_HasIntersection(&playerRect, &enemyRect))
		{
			//you have collided!
			//lose a life and reset the map
			CollideWithBullet();
			break;
		}
	}
}

bool Level::MapCollision(SDL_Rect playerR)
{
	for (auto& wall : m_CollisionObjects)
	{
		auto wallPos = wall->GetWorldPosition();
		glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
		SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
			static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };

		//check if the rects intersect or not
		if (SDL_HasIntersection(&playerR, &wallRect))
		{
			//you have collided!
			return true;
		}
	}
	return false;
}

void Level::CollideWithDiamond(SDL_Rect playerRect)
{
	if (!m_Diamond) return;

	SDL_Rect diamondRect{ static_cast<int>(m_Diamond->GetOwner()->GetWorldPosition().x),
		static_cast<int>(m_Diamond->GetOwner()->GetWorldPosition().y),
		static_cast<int>(m_Diamond->GetSize().x), static_cast<int>(m_Diamond->GetSize().y)};

	//check if the rects intersect or not
	if (SDL_HasIntersection(&playerRect, &diamondRect))
	{
		//now you should teleport
		TeleportPlayer();
	}
}

void Level::TeleportPlayer()
{
	GetOwner()->GetParent()->SetLocalPosition(FindNewPosition());
}

glm::vec2 Level::FindNewPosition()
{
	glm::vec2 newPos{};
	auto size = m_BaseTank->GetSize();

	while (newPos.x <= 0 || newPos.y <= 0 ||
		MapCollision(SDL_Rect{ static_cast<int>(newPos.x), static_cast<int>(newPos.y), 
			static_cast<int>(size.x), static_cast<int>(size.y) }))
	{
		newPos.x = (static_cast<float>(rand() % 450));
		newPos.y = (static_cast<float>(rand() % 410));
	}

	return newPos;
}
