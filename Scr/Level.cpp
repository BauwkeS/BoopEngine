#pragma once
#include "Level.h"
#include "Components/Events.h"
#include "../BoopEngine/Boop/Event/Event.h"
#include "GameLoader.h"
#include <SDL_rect.h>
#include "Components/Player.h"
#include "Components/Health.h"

Level::Level(boop::GameObject* owner, boop::Scene* pScene) : Component(owner),
m_SubjPlayer1{ std::make_unique<boop::Subject>() }, m_SubjPlayer2{ std::make_unique<boop::Subject>() }
//Level::Level(boop::GameObject* owner) : Component(owner), m_Subject{ std::make_unique<boop::Subject>() }
{
	//load up the vectors with the information about the scene yuo're in
	m_CollisionObjects = pScene->FindAllGameObjectByTag("collision");

	//get player info
	auto playerInfo = pScene->FindGameObjectByTag("p1");
	auto playerComp = playerInfo->GetComponent<booble::Player>();
	playerComp->GetTankBase()->SetStartPos(playerInfo->GetWorldPosition());
	if (playerComp) m_Players.emplace_back(playerComp);
	
	auto playerInfo2 = pScene->FindGameObjectByTag("p2");
	auto playerComp2 = playerInfo2->GetComponent<booble::Player>();
	playerComp2->GetTankBase()->SetStartPos(playerInfo2->GetWorldPosition());
	if (playerComp2) m_Players.emplace_back(playerComp2);

	//get enemy info
	auto enemyInfo = pScene->FindAllGameObjectByTag("enemy");
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

void Level::FixedUpdate()
{
	//check for collisions of the bullets and tanks

	CollideWithTank();
}

void Level::CollideWithBullet()
{
	//here you should check for your collisions

	///set bools for now, activated by buttons
	if (m_HitTank)
	{
		m_SubjPlayer1->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerKillTank")));
		m_HitTank = false;
	}
	if (m_HitRecognizer)
	{
		m_SubjPlayer1->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerKillRecognizer")));
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

	for (auto& player : m_Players)
	{
		//check if player runs in with another tank
		auto playerPos = player->GetOwner()->GetWorldPosition();
		glm::vec2 playerSize = player->GetTankBase()->GetSize();

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
				player->GetOwner()->GetComponent<Health>()->TakeDamage();
				player->GetTankBase()->ResetPosition();
				enemy->GetTankBase()->ResetPosition();
			}
		}
	}
}

void Level::CollideGameBounds()
{
	//check that the gameobject is within the game bounds
	//if not, set the position to the game bounds

}
