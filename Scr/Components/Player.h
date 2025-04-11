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
		Player(boop::GameObject* owner, int speed, const std::string spritePath);
		~Player() = default;

		void FixedUpdate() override;
		void Update() override;
		void Render() const override;

		/*void ChangeSpeed(int speed) { m_pTankBase->ChangeSpeed(speed) = speed; }
		int GetSpeed() const { return m_Speed; }*/

		int GetScore() const { return m_Score; }
		void OnNotify(boop::Event event) override;

		//glm::vec2 GetSize() const { return m_Size; }

		//void ResetPosition();
		//void SetStartPos(glm::vec2 pos) { m_StartPos = pos; }

		//add input
		void AddKeyboardMovement(const std::string& sceneName);
		void AddControllerMovement(const std::string& sceneName);

		BaseTank* GetTankBase() const { return m_pTankBase; }

	private:
		//int m_Speed{};
		int m_Score{};
		//glm::vec2 m_Size{};
	//	glm::vec2 m_StartPos{};

		std::unique_ptr<boop::Subject> m_Subject{};

		BaseTank* m_pTankBase{};
	};

}