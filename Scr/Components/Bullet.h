#pragma once
#include "../../BoopEngine/Boop/GameObject.h"


class Bullet : public boop::Component
{
public:
	Bullet(boop::GameObject* owner, glm::vec2 speed, std::vector<boop::GameObject*> collision);
	~Bullet() = default;

	void FixedUpdate() override;
	void Update() override;
	void Render() const override;

private:
	glm::vec2 m_Dir{};
	std::vector<boop::GameObject*> m_CollisionObjects{};
	float m_Speed{100.f};

	int m_BounceCount{};

	void CheckCollision();
};
