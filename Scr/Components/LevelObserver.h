#pragma once
#include <memory>
#include "../../BoopEngine/Boop/Event/Observer.h"
#include "../../BoopEngine/Boop/Event/Event.h"



class boop::GameObject;

class LevelObserver : public boop::Observer
{
public:
	LevelObserver() {};
	~LevelObserver() = default;

	void OnNotify(boop::Event event) override;
};
