#pragma once

#include "../BoopEngine/Boop/Input/Command.h"
#include "../BoopEngine/Boop/DeltaTime.h"

#include "Player.h"
#include <iostream>
#include <memory>
#include <glm/ext/vector_float2.hpp>

//COMMANDS HERE
namespace boop
{
	class GameObject;
	class Command;
	class SpriteComponent;
}

namespace booble
{
	//MOVEMENT
	class WalkCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
		glm::vec2 m_Speed;
	public:
		WalkCommand(boop::GameObject* component, glm::vec2 speed)
			: m_pGameObject{ component }, m_Speed{ speed } {}
		//make sure you can walk without jumping
		~WalkCommand() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute() override {

			m_pGameObject->SetLocalPosition(m_pGameObject->GetLocalPosition().x + (m_Speed.x * boop::DeltaTime::GetInstance().GetDeltaTime()),
				m_pGameObject->GetLocalPosition().y + (m_Speed.y * boop::DeltaTime::GetInstance().GetDeltaTime()));

		};

		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;

	};

	//class StopWalkingCommand final : public boop::Command {
	//private:
	//	boop::GameObject* m_pGameObject;
	//public:
	//	StopWalkingCommand(boop::GameObject* component)
	//		: m_pGameObject{ component } {}
	//	//make sure you can walk without jumping
	//	~StopWalkingCommand() { m_pGameObject = nullptr; delete m_pGameObject; };

	//	void Execute(float) override {

	//		//FOR THE PLAYER
	//		auto playerComp = m_pGameObject->GetComponent<Player>();
	//		if (playerComp)
	//		{

	//		}


	//	};

	//	StopWalkingCommand(const StopWalkingCommand& other) = delete;
	//	StopWalkingCommand(StopWalkingCommand&& other) = delete;
	//	StopWalkingCommand& operator=(const StopWalkingCommand& other) = delete;
	//	StopWalkingCommand& operator=(StopWalkingCommand&& other) = delete;

	//};

	//class JumpCommand final : public boop::Command {
	//private:
	//	boop::GameObject* m_pGameObject;
	//	float m_JumpStrength;
	//public:
	//	JumpCommand(boop::GameObject* component, float jumpStrength)
	//		: m_pGameObject{ component }, m_JumpStrength{ jumpStrength } {}

	//	~JumpCommand() { m_pGameObject = nullptr; delete m_pGameObject; };

	//	void Execute(float) override {
	//		auto playerComp = m_pGameObject->GetComponent<Player>();
	//		if (playerComp) {
	//			//playerComp->StartJump(m_JumpStrength);


	//			//add jumping
	//			//if (m_Jump) playerComp->Jump(m_JumpForce);

	//		}
	//	}

	//	JumpCommand(const JumpCommand& other) = delete;
	//	JumpCommand(JumpCommand&& other) = delete;
	//	JumpCommand& operator=(const JumpCommand& other) = delete;
	//	JumpCommand& operator=(JumpCommand&& other) = delete;
	//};
};
