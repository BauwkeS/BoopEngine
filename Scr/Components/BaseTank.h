#pragma once
#include <memory>
#include "../../BoopEngine/Boop/GameObject.h"
#include <glm/vec2.hpp>
#include "../../BoopEngine/Boop/Event/Observer.h"

namespace boop {
	class GameObject;
	class CollisionComponent;
	class Component;
	class Scene;
}

class BaseTank : public boop::Component
{
public:
	BaseTank(boop::GameObject* owner, int speed, const std::string spritePath);
	~BaseTank() = default;

	void ChangeSpeed(int speed) { m_Speed = speed; }
	int GetSpeed() const { return m_Speed; }

	glm::vec2 GetSize() const { return m_Size; }

	void ResetPosition();
	void SetStartPos(glm::vec2 pos) { m_StartPos = pos; }


	void FixedUpdate() override;
	void Update() override;
	void Render() const override;

private:
	int m_Speed{};
	glm::vec2 m_Size{};
	glm::vec2 m_StartPos{};
};

