#pragma once

#include "../BoopEngine/Boop/Input/Command.h"
#include "../BoopEngine/Boop/DeltaTime.h"

#include "Components/Player.h"
#include <iostream>
#include <memory>
#include <glm/ext/vector_float2.hpp>
#include "Components/Health.h"
#include "Level.h"

#include "../BoopEngine/Boop/Scene/Scene.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"

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

	//TEST
	class TestGetHitCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
	public:
		TestGetHitCommand(boop::GameObject* component)
			: m_pGameObject{ component } {
		}
		~TestGetHitCommand() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute() override {
			m_pGameObject->GetComponent<Health>()->TakeDamage();
		};

		TestGetHitCommand(const TestGetHitCommand& other) = delete;
		TestGetHitCommand(TestGetHitCommand&& other) = delete;
		TestGetHitCommand& operator=(const TestGetHitCommand& other) = delete;
		TestGetHitCommand& operator=(TestGetHitCommand&& other) = delete;

	};
	class TestHitTank final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
	public:
		TestHitTank(boop::GameObject* component)
			: m_pGameObject{ component } {
		}
		~TestHitTank() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute() override {
			m_pGameObject->GetComponent<Level>()->SetHitTank();
			//boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("Level")->GetComponent<Level>()->SetHitTank();
		};

		TestHitTank(const TestHitTank& other) = delete;
		TestHitTank(TestHitTank&& other) = delete;
		TestHitTank& operator=(const TestHitTank& other) = delete;
		TestHitTank& operator=(TestHitTank&& other) = delete;

	};
	class TestHitRecognizer final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
	public:
		TestHitRecognizer(boop::GameObject* component)
			: m_pGameObject{ component } {
		}
		~TestHitRecognizer() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute() override {
			m_pGameObject->GetComponent<Level>()->SetHitRecognizer();
			//boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("Level")->GetComponent<Level>()->SetHitRecognizer();
		};

		TestHitRecognizer(const TestHitRecognizer& other) = delete;
		TestHitRecognizer(TestHitRecognizer&& other) = delete;
		TestHitRecognizer& operator=(const TestHitRecognizer& other) = delete;
		TestHitRecognizer& operator=(TestHitRecognizer&& other) = delete;

	};
};
