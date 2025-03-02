#pragma once
#include <SDL.h>
#include "BoopEngine/Boop/Components/Component.h"

class TimeExComp : public boop::Component
{
public:
	TimeExComp(boop::GameObject* const ownerPtr);
	~TimeExComp() override;

	TimeExComp(const TimeExComp& other) = delete;
	TimeExComp(TimeExComp&& other) = delete;
	TimeExComp& operator=(const TimeExComp& other) = delete;
	TimeExComp& operator=(TimeExComp&& other) = delete;

	void FixedUpdate(float) override {}
	void Update(float deltaTime) override;
	void Render() const override;


private:
	SDL_Renderer* m_Renderer;
};