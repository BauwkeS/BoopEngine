#pragma once
#include "../../BoopEngine/Boop/GameObject.h"

class Enemy;
class Level;

class Bullet : public boop::Component
{
public:
	Bullet(boop::GameObject* owner, glm::vec2 speed, Level* levelinfo);
	~Bullet() = default;

	void FixedUpdate() override;
	void Update() override;
	void Render() const override;

private:
	glm::vec2 m_Dir{};
	Level* m_LevelInfo{};
	float m_Speed{300.f};

	int m_BounceCount{0};

	void CheckCollision();
};
