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
	PlayerHit playerHit{};
	NotifyObserver(playerHit);
	if (m_Health <= 0)
	{
		PlayerDied playerDied{};
		//m_Subject->NotifyObserver(*GetOwner(), playerDied);
		NotifyObserver(playerDied);
	}
}
