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

	//int m_TimingSizeEx1{ 1000000 };
	//int* m_ArrEx1;

	//constexpr int timings[11]{ 1,2,4,8,16,32,64,128,256,512,1024 };
	//int m_TimingsEx1[11]{};
	//int m_SamplesEx1{10};



	void Ex1() const;
	void Ex2() const;
};

struct transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	transform local;
	int id;
};

class GameObject3DAlt
{
public:
	transform* local;
	int id;
};