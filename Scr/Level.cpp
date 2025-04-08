#include "Level.h"
#include "Components/Events.h"
#include "../BoopEngine/Boop/Event/Event.h"

Level::Level(boop::GameObject* owner) : Component(owner), m_Subject{ std::make_unique<boop::Subject>() }
{
}

void Level::FixedUpdate()
{
	//check for collisions of the bullets and tanks

	CollideWithBullet();
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
}

void Level::CollideGameBounds()
{
	//check that the gameobject is within the game bounds
	//if not, set the position to the game bounds

}
