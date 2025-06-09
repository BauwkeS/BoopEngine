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
		if (event.id == boop::make_sdbm_hash("PlayerKillTank")
			|| event.id == boop::make_sdbm_hash("PlayerKillRecognizer"))
		{
			int score = GetOwner()->GetComponent<Player>()->GetScore();
			SetText("Score: " + std::to_string(score));
		}
	}

}
