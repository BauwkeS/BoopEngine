#pragma once
#include "Level.h"
#include "Components/Events.h"
#include "../BoopEngine/Boop/Event/Event.h"
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
	CollideWithBullet();
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
}

void Level::CollideWithBullet()
{
	//here you should check for your collisions

	///set bools for now, activated by buttons
	if (m_HitTank)
	{
		m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerKillTank")));
		m_HitTank = false;
	}
	if (m_HitRecognizer)
	{
		m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerKillRecognizer")));
		m_HitRecognizer = false;
	}
	//THIS IS WRONG PLEASE FIX WTF THIS IS
}

void Level::CollideWithTank(SDL_Rect playerRect)
{
	
		//check if player runs in with another tank
		for (auto& enemy : m_Enemies)
		{
			auto enemyPos = enemy->GetOwner()->GetWorldPosition();
			glm::vec2 enemySize = enemy->GetTankBase()->GetSize();

			SDL_Rect enemyRect{ static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y),
				static_cast<int>(enemySize.x), static_cast<int>(enemySize.y) };

			//check if the rects intersect or not
			if (SDL_HasIntersection(&playerRect, &enemyRect))
			{
				//you have collided!
				//lose a life and reset the map
				m_BaseTank->GetOwner()->GetComponent<Health>()->TakeDamage();
				m_BaseTank->ResetPosition();
				enemy->GetTankBase()->ResetPosition();
				break;
			}
	}
}

void Level::MapCollision(SDL_Rect)
{
	//check if player runs in with another tank
	//for (auto& wall : m_CollisionObjects)
	//{
	//	auto wallPos = wall->GetWorldPosition();
	//	glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
	//	SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
	//		static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };
	//	//check if the rects intersect or not
	//	if (SDL_HasIntersection(&playerRect, &wallRect))
	//	{
	//		//you have collided!
	//		m_Player->GetTankBase()->ResetPosition();
	//		break;
	//	}
	//}
}
