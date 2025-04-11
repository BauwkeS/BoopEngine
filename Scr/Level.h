#pragma once
#include "../BoopEngine/Boop/Components/Component.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Event/Subject.h"
#include "../BoopEngine/Boop/Scene/Scene.h"
#include "Components/Enemy.h"
#include <memory>

namespace boop
{
	class Scene;
}

namespace booble
{
	class Player;
}

class Level final : public boop::Component
{
public:
	//Level(boop::GameObject* owner);
	Level(boop::GameObject* owner, boop::Scene* pScene);
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

	boop::Subject* GetPlayer1Sub() const { return m_SubjPlayer1.get(); }
	boop::Subject* GetPlayer2Sub() const { return m_SubjPlayer2.get(); }

private:
	//test variables when button set
	bool m_HitTank{};
	bool m_HitRecognizer{};

	std::unique_ptr<boop::Subject> m_SubjPlayer1{};
	std::unique_ptr<boop::Subject> m_SubjPlayer2{};

	//vector of all the wall objects you cannot pass
	std::vector<boop::GameObject*> m_CollisionObjects{};
	//vector of the players
	std::vector<booble::Player*> m_Players{};
	//vector of the enemies
	std::vector<Enemy*> m_Enemies{};


	//collision functions
	void CollideWithBullet();
	void CollideWithTank();
	void CollideGameBounds();
};
