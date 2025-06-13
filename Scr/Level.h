#pragma once
#include "../BoopEngine/Boop/Components/Component.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Event/Subject.h"
#include "../BoopEngine/Boop/Scene/Scene.h"
#include "Components/Enemy.h"
#include <memory>
#include <SDL_rect.h>
#include <glm/vec2.hpp>

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

	void ResetPlayerCollision(boop::Scene* scene, bool alsoSetPos=true);

	boop::Subject* GetSubject() const { return m_Subject.get(); }

	//getters
	std::vector<boop::GameObject*> GetCollisionObjects() const { return m_CollisionObjects; }
	std::vector<Enemy*> GetEnemies() const { return m_Enemies; }

	void CollideWithBullet();

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
	boop::TextureComponent* m_Diamond{};


	//collision functions
	void CollideWithTank(SDL_Rect playerRect);
	void CollideWithDiamond(SDL_Rect playerRect);

	void TeleportPlayer();
	glm::vec2 FindNewPosition();
	bool MapCollision(SDL_Rect playerRect);

	void ResetBullets();
};
