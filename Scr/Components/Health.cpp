#pragma once
#include "Health.h"
#include "Events.h"

Health::Health(boop::GameObject* owner, int health)
	: Component(owner), Subject(), m_Health(health), m_MaxHealth(health)
{
}

void Health::TakeDamage(int damage)
{
	m_Health -= damage;
	NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerHit")));
	if (m_Health <= 0)
	{
		NotifyObserver(boop::Event(boop::make_sdbm_hash("PlayerDied")));
	}
}
