#pragma once
#include "../../BoopEngine/Boop/GameObject.h"
#include <SDL_rect.h>

class Enemy;
class Level;
class GameObject;

class Bullet : public boop::Component
{
public:
	Bullet(boop::GameObject* owner, glm::vec2 speed, Level* levelinfo, bool enemyBullet={false});
	~Bullet() = default;

	void FixedUpdate() override;
	void Update() override;
	void Render() const override;

private:
	glm::vec2 m_Dir{};
	Level* m_LevelInfo{};

	boop::GameObject* m_Player1{ nullptr };
	boop::GameObject* m_Player2{ nullptr };
	
	bool m_EnemyBullet{ false };

	float m_Speed{300.f};

	int m_BounceCount{0};
	

	void CheckCollisionPlayerBullet();
	void CheckCollisionEnemyBullet();

	void CheckCollisionWall(SDL_Rect bullet);
};
