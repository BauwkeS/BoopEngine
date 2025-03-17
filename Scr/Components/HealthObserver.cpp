#pragma once
#include "HealthObserver.h"
#include "../../BoopEngine/Boop/GameObject.h"
#include "Events.h"
#include "Health.h"

HealthObserver::HealthObserver(boop::GameObject* owner)
	: TextComponent(owner)
{
	int starthealth = owner->GetComponent<Health>()->GetHealth();
	SetText("Health: " + std::to_string(starthealth));
}

void HealthObserver::OnNotify(boop::Event event)
{
	//if (event == PlayerDied) gameObject
	//{
	//	//do something
	//}
	//PlayerDied playerDied{};
	//íf(event == playerDied)
	//{
	//	//do something
	//}

	

	if (event.id == boop::make_sdbm_hash("PlayerHit"))
	{
		int health = GetOwner()->GetComponent<Health>()->GetHealth();
		SetText("Health: " + std::to_string(health));
	}
	else if (event.id == boop::make_sdbm_hash("PlayerDied"))
	{
		int health = GetOwner()->GetComponent<Health>()->GetHealth();
		SetText("Health: " + std::to_string(health) + " - YOU DIED");
	}
	
}