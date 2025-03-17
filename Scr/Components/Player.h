#pragma once
#include <memory>
#include "../../BoopEngine/Boop/GameObject.h"
#include <glm/vec2.hpp>
#include "../../BoopEngine/Boop/Event/Subject.h"
#include "../../BoopEngine/Boop/Event/Observer.h"

namespace boop {
	class GameObject;
	class CollisionComponent;
	class Component;
}

namespace booble 
{
	class Player : public boop::Component, public boop::Observer, public boop::Subject
	{
	public:
		Player(boop::GameObject* owner, float speed);
		~Player() = default;

		void FixedUpdate() override;
		void Update() override;
		void Render() const override;

		void ChangeSpeed(float speed) { m_Speed = speed; }
		float GetSpeed() const { return m_Speed; }

		int GetScore() const { return m_Score; }
		void OnNotify(boop::Event event) override;
	private:
		float m_Speed{};
		int m_Score{};
	};

}