#pragma once
#include "../../BoopEngine/Boop/GameObject.h"


class Bullet : public boop::Component
{
public:
	Bullet(boop::GameObject* owner, const std::string& spritePath, glm::vec2 speed);
	~Bullet() = default;

	void FixedUpdate() override;
	void Update() override;
	void Render() const override;

private:
	glm::vec2 m_Dir{};
};
