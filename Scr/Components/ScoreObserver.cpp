#include "ScoreObserver.h"
#include "Events.h"
#include "Player.h"

namespace booble {
	ScoreObserver::ScoreObserver(boop::GameObject* owner)
		: TextComponent(owner, "Score: 0")
	{
	}

	void ScoreObserver::OnNotify(boop::Event& event)
	{
		if (dynamic_cast<PlayerKillTank*>(&event)
			|| dynamic_cast<PlayerKillRecognizer*>(&event))
		{
			int score = GetOwner()->GetComponent<Player>()->GetScore();
			SetText("Score: " + std::to_string(score));
		}
	}

}
