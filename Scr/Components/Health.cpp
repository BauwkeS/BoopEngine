#pragma once
#include "Health.h"
#include "Events.h"

Health::Health(boop::GameObject* owner, int health)
	: Component(owner), m_Health(health), m_MaxHealth(health), m_Subject{ std::make_unique<boop::Subject>() }
{
}

void Health::TakeDamage(int damage)
{
	m_Health -= damage;
	m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerHit")));
	if (m_Health <= 0)
	{
		m_Subject->NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerDied")));
	}
}
