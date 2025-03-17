#pragma once
#include "../BoopEngine/Boop/Components/Component.h"
#include "../BoopEngine/Boop/Event/Subject.h"

class Level final : public boop::Component, public boop::Subject
{
public:
	Level(boop::GameObject* owner);
	~Level() = default;
	
	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;

	void Update() override {};
	void Render() const override {};

	void FixedUpdate() override;

	void CollideWithBullet();

	void SetHitTank() { m_HitTank = true; }
	void SetHitRecognizer() { m_HitRecognizer = true; }

private:
	//test variables when button set
	bool m_HitTank{};
	bool m_HitRecognizer{};
};
