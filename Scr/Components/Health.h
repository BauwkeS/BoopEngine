#pragma once
#include <memory>
#include "../../BoopEngine/Boop/Components/Component.h"
#include "../../BoopEngine/Boop/Event/Subject.h"

class Health : public boop::Component
{
	public:
	Health(boop::GameObject* owner, int health);
	~Health() = default;
	void FixedUpdate() override {};
	void Update() override {};
	void Render() const override {};
	
	int TakeDamage(int damage=1);
	int GetHealth() const { return m_Health; }

	boop::Subject* GetSubject() const { return m_Subject.get(); }

private:
	int m_Health{};
	int m_MaxHealth{};

	std::unique_ptr<boop::Subject> m_Subject{};
};
 