#include "ScoreObserver.h"
#include "Events.h"
#include "Player.h"

namespace booble {
	ScoreObserver::ScoreObserver(boop::GameObject* owner)
		: TextComponent(owner, "Score: 0")
	{
	}

	void ScoreObserver::OnNotify(boop::Event event)
	{
		//if (event.id == boop::make_sdbm_hash("PlayerKillTank")
		//	|| event.id == boop::make_sdbm_hash("PlayerKillRecognizer"))
		//{
		//	m_Score += GetOwner()->GetComponent<Player>()->GetScore();
		//	
		//}
		if (event.id == boop::make_sdbm_hash("PlayerKillTank")) {
			m_Score += 100;
		}
		if (event.id == boop::make_sdbm_hash("PlayerKillRecognizer")) {
			m_Score += 250;
		}
		SetText("Score: " + std::to_string(m_Score));
	}

}
