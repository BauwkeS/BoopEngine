#pragma once
#include "../BoopEngine/Boop/Components/Component.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Event/Subject.h"
#include "../BoopEngine/Boop/Scene/Scene.h"
#include "Components/Enemy.h"
#include <memory>
#include <SDL_rect.h>

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

	void ResetPlayerCollision(boop::Scene* scene);;

	boop::Subject* GetSubject() const { return m_Subject.get(); }

	//getters
	std::vector<boop::GameObject*> GetCollisionObjects() const { return m_CollisionObjects; }

private:
	//test variables when button set
	bool m_HitTank{};
	bool m_HitRecognizer{};

	std::unique_ptr<boop::Subject> m_Subject{};

	//booble::Player* m_Player{};
	BaseTank* m_BaseTank{};

	//vector of all the wall objects you cannot pass
	std::vector<boop::GameObject*> m_CollisionObjects{};
	//vector of the enemies
	std::vector<Enemy*> m_Enemies{};


	//collision functions
	void CollideWithBullet();
	void CollideWithTank(SDL_Rect playerRect);
	void MapCollision(SDL_Rect playerRect);
};
