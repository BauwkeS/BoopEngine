#pragma once
#include "Health.h"
#include "Events.h"
#include "Player.h"
#include "Enemy.h"

Health::Health(boop::GameObject* owner, int health)
	: Component(owner), m_Health(health), m_MaxHealth(health), m_Subject{ std::make_unique<boop::Subject>() }
{
}

int Health::TakeDamage(int damage)
{
	m_Health -= damage;


	if (GetOwner()->GetComponent<booble::Player>()) {
		m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerHit")));
		if (m_Health <= 0)
		{
			m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerDied")));
		}
	}
	else
	{
		if (m_Health <= 0 && GetOwner()->GetComponent<BlueTankEnemy>())
		{
			//m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("EnemyHitBlueTank")));
			//if (m_Health <= 0)
			//{
			//	m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerKillTank")));
			//	GetOwner()->SetToDelete(); //delete the enemy
			//}
			GetOwner()->SetToDelete(); //delete the enemy
			return 1;
		}
		else if (m_Health <= 0 && GetOwner()->GetComponent<Enemy>())
		{
			//m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("EnemyHitRecognizer")));
			//if (m_Health <= 0)
			//{
			//	m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerKillRecognizer")));
			//	GetOwner()->SetToDelete(); //delete the enemy
			//}
			GetOwner()->SetToDelete(); //delete the enemy
			return 2;
		}
		
	}

	return 0;
}
