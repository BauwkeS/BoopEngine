#pragma once

#include "../BoopEngine/Boop/Input/Command.h"

#include "Player.h"
#include <iostream>
#include <memory>

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
		float m_Speed;
		bool m_Jump;
		float m_JumpForce;
	public:
		WalkCommand(boop::GameObject* component, float speed, bool jump = false, float jumpForce = 0.0f)
			: m_pGameObject{ component }, m_Speed{ speed }, m_Jump{ jump }, m_JumpForce{ jumpForce } {}
		//make sure you can walk without jumping
		~WalkCommand() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute(float) override {

			//FOR THE PLAYER
			auto playerComp = m_pGameObject->GetComponent<Player>();
			if (playerComp)
			{
				
				//if (m_Jump) playerComp->Jump(m_JumpForce);
			}


		};

		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;

	};

	class StopWalkingCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
	public:
		StopWalkingCommand(boop::GameObject* component)
			: m_pGameObject{ component } {}
		//make sure you can walk without jumping
		~StopWalkingCommand() { m_pGameObject = nullptr; delete m_pGameObject; };

		void Execute(float) override {

			//FOR THE PLAYER
			auto playerComp = m_pGameObject->GetComponent<Player>();
			if (playerComp)
			{

			}


		};

		StopWalkingCommand(const StopWalkingCommand& other) = delete;
		StopWalkingCommand(StopWalkingCommand&& other) = delete;
		StopWalkingCommand& operator=(const StopWalkingCommand& other) = delete;
		StopWalkingCommand& operator=(StopWalkingCommand&& other) = delete;

	};

	class JumpCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
		float m_JumpStrength;
	public:
		JumpCommand(boop::GameObject* component, float jumpStrength)
			: m_pGameObject{ component }, m_JumpStrength{ jumpStrength } {}

		~JumpCommand() { m_pGameObject = nullptr; delete m_pGameObject; };

		void Execute(float) override {
			auto playerComp = m_pGameObject->GetComponent<Player>();
			if (playerComp) {
				//playerComp->StartJump(m_JumpStrength);


				//add jumping
				//if (m_Jump) playerComp->Jump(m_JumpForce);

			}
		}

		JumpCommand(const JumpCommand& other) = delete;
		JumpCommand(JumpCommand&& other) = delete;
		JumpCommand& operator=(const JumpCommand& other) = delete;
		JumpCommand& operator=(JumpCommand&& other) = delete;
	};
};
