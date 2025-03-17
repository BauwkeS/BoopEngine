#pragma once
#include <memory>
#include "../../BoopEngine/Boop/Components/TextComponent.h"
#include "../../BoopEngine/Boop/Event/Observer.h"

class boop::GameObject;

class HealthObserver : public boop::TextComponent, public boop::Observer
{
public:
	HealthObserver(boop::GameObject* owner);
	~HealthObserver() = default;

	void OnNotify(boop::Event event) override;
private:
	
};
