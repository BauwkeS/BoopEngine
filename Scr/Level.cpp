#pragma once
#include "Level.h"
#include "Components/Events.h"
#include "../BoopEngine/Boop/Event/Event.h"
#include "GameLoader.h"
#include <SDL_rect.h>
#include "Components/Player.h"
#include "Components/Health.h"

Level::Level(boop::GameObject* owner) : Component(owner),
m_Subject{ std::make_unique<boop::Subject>() }
//Level::Level(boop::GameObject* owner) : Component(owner), m_Subject{ std::make_unique<boop::Subject>() }
{
	/*auto levelItems = std::make_unique<boop::GameObject>();
	levelItems->SetTag("level");
	auto levelComp = levelItems->AddComponent<Level>();
	levelComp->GetSubject()->AddObserver(player * here);*/

	// The parent should be the player GameObject
	//if (owner->GetParent())
	//{
	//	m_Player = owner->GetParent()->GetComponent<booble::Player>();

	//	// If you need to do any setup with the player
	//	if (m_Player)
	//	{
	//		m_Subject->AddObserver(m_Player); // Example: make player observe level events
	//	}
	//}
}

void Level::FixedUpdate()
{
	//check for collisions of the bullets and tanks

	CollideWithTank();
}

void Level::ResetPlayerCollision(boop::Scene* scene)
{
	m_CollisionObjects.clear();
	m_Enemies.clear();

	//load up the vectors with the information about the scene yuo're in
	m_CollisionObjects = scene->FindAllGameObjectByTag("collision");

	//get player info
	//auto playerInfo = pScene->FindGameObjectByTag("p1");
	auto playerComp = GetOwner()->GetParent()->GetComponent<booble::Player>();
	playerComp->GetTankBase()->SetStartPos(GetOwner()->GetWorldPosition());
	if (playerComp) m_Player = playerComp;
	
	
	/*if (playerComp) m_Players.emplace_back(playerComp);

	if (gamemode == static_cast<int>(booble::GameMode::MULTIPLAYER))
	{
		auto playerInfo2 = pScene->FindGameObjectByTag("p2");
		auto playerComp2 = playerInfo2->GetComponent<booble::Player>();
		playerComp2->GetTankBase()->SetStartPos(playerInfo2->GetWorldPosition());
		if (playerComp2) m_Players.emplace_back(playerComp2);
	}
	else if (gamemode == static_cast<int>(booble::GameMode::COOP))
	{
		auto playerInfo2 = pScene->FindGameObjectByTag("p2");
		auto playerComp2 = playerInfo2->GetComponent<booble::Player>();
		playerComp2->GetTankBase()->SetStartPos(playerInfo2->GetWorldPosition());
		if (playerComp2) m_Players.emplace_back(playerComp2);
	}*/
	//auto playerInfo2 = pScene->FindGameObjectByTag("p2");
	//auto playerComp2 = playerInfo2->GetComponent<booble::Player>();
	//playerComp2->GetTankBase()->SetStartPos(playerInfo2->GetWorldPosition());
	//if (playerComp2) m_Players.emplace_back(playerComp2);

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

//void Level::FindPlayer()
//{
//	// The parent should be the player GameObject
//		if (GetOwner()->GetParent())
//		{
//			m_Player = GetOwner()->GetParent()->GetComponent<booble::Player>();
//
//			// If you need to do any setup with the player
//			if (m_Player)
//			{
//				m_Subject->AddObserver(m_Player); // Example: make player observe level events
//			}
//		}
//}

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

void Level::CollideWithTank()
{
	//check if the player collides with a tank?
	//check for different gamemodes

	//switch (booble::GameLoader::GetInstance().GetSelectedGamemode())
	//{
	//case static_cast<int>(booble::GameMode::SINGLEPLAYER):
	//	//check for singleplayer
	//	break;
	//case static_cast<int>(booble::GameMode::MULTIPLAYER):
	//	//check for multiplayer
	//	break;
	//case static_cast<int>(booble::GameMode::COOP):
	//	//check for coop
	//	break;
	//default:
	//	break;
	//}

	//check now for another player, but change later to-do an enemy tank

	//for (auto& player : m_Players)
	//{
		//check if player runs in with another tank
		auto playerPos = GetOwner()->GetWorldPosition();
		glm::vec2 playerSize = m_Player->GetTankBase()->GetSize();

		SDL_Rect playerRect{ static_cast<int>(playerPos.x), static_cast<int>(playerPos.y),
			static_cast<int>(playerSize.x), static_cast<int>(playerSize.y) };

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
				m_Player->GetOwner()->GetComponent<Health>()->TakeDamage();
				m_Player->GetTankBase()->ResetPosition();
				enemy->GetTankBase()->ResetPosition();
				break;
			}
	//	}
	}
}

void Level::CollideGameBounds()
{
	//check that the gameobject is within the game bounds
	//if not, set the position to the game bounds

}
