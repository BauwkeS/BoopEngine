#pragma once
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../BoopEngine/Boop/Components/Component.h"
#include "../BoopEngine/Boop/States.h"
#include "States.h"

//player needs the states
//the input ?
//lives
//score?
//movement

namespace booble
{
	class Player : public boop::Component
	{
	public:
		boop::GameObject* CreatePlayer();
		Player(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows,
			const float frameSec, const int startPicIndex, const int AmountPics, const float scale, boop::Collision* collision = nullptr);

		boop::SpriteComponent* GetSprite() const { return m_SpriteComp.get(); }
		PlayerStateMachine* GetStateMachine() { return m_StateMachine.get(); }

		void FixedUpdate(float deltaTime) override { deltaTime; };
		void Update(float deltaTime) override { deltaTime; };
		void LateUpdate(float deltaTime) override { deltaTime; };
		void Render() const override { };

	private:
		std::unique_ptr<boop::SpriteComponent> m_SpriteComp{};

		void InitCommands();
		
		
		//States:
		std::unique_ptr<WalkState> m_WalkState{};
		std::unique_ptr<AttackState> m_AttackState{};
		std::unique_ptr<HurtState> m_HurtState{};
		std::unique_ptr<PlayerStateMachine> m_StateMachine{};
	};

}