#include "Level.h"
#include "Components/Events.h"

Level::Level(boop::GameObject* owner) : Component(owner), Subject()
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
		PlayerKillTank playerKillTank{};
		NotifyObserver(playerKillTank);
		m_HitTank = false;
	}
	if (m_HitRecognizer)
	{
		PlayerKillRecognizer playerKillRecognizer{};
		NotifyObserver(playerKillRecognizer);
		m_HitRecognizer = false;
	}
}
