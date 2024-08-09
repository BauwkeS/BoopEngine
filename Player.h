#pragma once
#include "BoopEngine/Boop/GameObject.h"
#include "BoopEngine/Boop/Components/SpriteComponent.h"
#include "BoopEngine/Boop/States.h"

//player needs the states
//the input ?
//lives
//score?
//movement



class Player
{
public:
	Player(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows,
		const float frameSec, const int startPicIndex, const int AmountPics, const float scale, boop::Collision* collision = nullptr);

	boop::SpriteComponent* GetSprite() const { return m_SpriteComp.get(); }

private:
	std::unique_ptr<boop::SpriteComponent> m_SpriteComp{};



};


//PLAYER STATE INFORMATION
class PlayerStateMachine : boop::StateMachine
{
	
};

class WalkState : boop::BaseState
{
public:
	WalkState() = default;
	~WalkState() = default;
	void HandleInput(boop::Component& gameObject) override;

	void Update(float deltaTime) override;
	void Render(float deltaTime) override;

	void OnEnter() override;
	void OnExit() override;
};
