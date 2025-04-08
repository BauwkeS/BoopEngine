#pragma once
#include "../BoopEngine/Boop/Components/Component.h"
#include "../BoopEngine/Boop/Event/Subject.h"
#include <memory>

class Level final : public boop::Component
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


	void SetHitTank() { m_HitTank = true; }
	void SetHitRecognizer() { m_HitRecognizer = true; }

	boop::Subject* GetSubject() const { return m_Subject.get(); }

private:
	//test variables when button set
	bool m_HitTank{};
	bool m_HitRecognizer{};

	std::unique_ptr<boop::Subject> m_Subject{};


	//collision functions
	void CollideWithBullet();
	void CollideWithTank() {};
	void CollideGameBounds();
};
