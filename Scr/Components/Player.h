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
	class Scene;
}

namespace booble 
{
	class Player : public boop::Component, public boop::Observer, public boop::Subject
	{
	public:
		Player(boop::GameObject* owner, int speed, const std::string spritePath);
		~Player() = default;

		void FixedUpdate() override;
		void Update() override;
		void Render() const override;

		void ChangeSpeed(int speed) { m_Speed = speed; }
		int GetSpeed() const { return m_Speed; }

		int GetScore() const { return m_Score; }
		void OnNotify(boop::Event event) override;

		//add input
		void AddKeyboardMovement(const std::string& sceneName);
		void AddControllerMovement(const std::string& sceneName);

	private:
		int m_Speed{};
		int m_Score{};
	};

}