#pragma once
#include <memory>
#include "../../BoopEngine/Boop/Event/Observer.h"
#include "../../BoopEngine/Boop/Event/Event.h"
#include <string>


class boop::GameObject;

class LevelObserver : public boop::Observer
{
public:
	LevelObserver();
	~LevelObserver() = default;

	void OnNotify(boop::Event event) override;

private:
	struct EndData {
		int score;
		std::string playerWon; // 1 for player 1, 2 for player 2, 0 for coop
	};
	
	void SetUpEndScreen();
	EndData GetEndData();
};
