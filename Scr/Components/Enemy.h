#pragma once
#include <memory>
#include "../../BoopEngine/Boop/GameObject.h"
#include <glm/vec2.hpp>
#include "../../BoopEngine/Boop/Event/Observer.h"
#include "BaseTank.h"

namespace boop {
	class GameObject;
	class Component;
	class Scene;
	class Subject;
}

class Enemy : public boop::Component
	{
	public:
		Enemy(boop::GameObject* owner, int speed, const std::string spritePath);
		~Enemy() = default;

		void FixedUpdate() override;
		void Update() override;
		void Render() const override;

		BaseTank* GetTankBase() const { return m_pTankBase; }

	private:
		BaseTank* m_pTankBase{};
	};
