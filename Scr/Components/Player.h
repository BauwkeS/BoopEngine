#pragma once
#include <memory>
#include "../../BoopEngine/Boop/GameObject.h"
#include <glm/vec2.hpp>
#include "../../BoopEngine/Boop/Event/Observer.h"
#include "BaseTank.h"

namespace boop {
	class GameObject;
	class CollisionComponent;
	class Component;
	class Scene;
	class Subject;
}

namespace booble 
{
	class Player : public boop::Component, public boop::Observer
	{
	public:
		Player(boop::GameObject* owner);
		~Player() = default;

		void FixedUpdate() override;
		void Update() override;
		void Render() const override;
		int GetScore() const { return m_Score; }
		void OnNotify(boop::Event event) override;

		//add input
		void AddKeyboardMovement();
		void AddControllerMovement();

		//BaseTank* GetTankBase() const { return m_pTankBase; }

		boop::Subject* GetSubject() const { return m_Subject.get(); }

	private:
		int m_Score{};
		int m_Speed{};

		std::unique_ptr<boop::Subject> m_Subject{};

		//BaseTank* m_pTankBase{};
	};

}