#include "Bullet.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"
#include "../../BoopEngine/Boop/DeltaTime.h"
#include "Enemy.h"
#include "../Level.h"
#include "Player.h"
#include "Health.h"
#include "../../BoopEngine/Boop/Sound/ServiceLocator.h"

Bullet::Bullet(boop::GameObject* owner, glm::vec2 dir, Level* levelinfo, bool enemyBullet)
	: Component(owner), m_Dir{ dir }, m_LevelInfo{ levelinfo }, m_EnemyBullet{ enemyBullet }
{
	if (enemyBullet)
	{
		m_Player1 = boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("p1");
		m_Player2 = boop::SceneManager::GetInstance().GetActiveScene()->FindGameObjectByTag("p2");
		m_BounceCount = 4; //cannot bounce back
	}

	boop::ServiceLocator::GetSoundSystem()->PlaySound("Shoot.wav", 0.5f);
}

void Bullet::FixedUpdate()
{
	if (!GetOwner()->ToDelete())
	{
		if (!m_EnemyBullet) CheckCollisionPlayerBullet();
		else CheckCollisionEnemyBullet();
	}
	
}

void Bullet::Update()
{
	
}

void Bullet::Render() const
{

}

void Bullet::CheckCollisionPlayerBullet()
{
	//with speed
	auto moveX = (m_Dir.x * m_Speed * boop::DeltaTime::GetInstance().GetDeltaTime());
	auto moveY = (m_Dir.y * m_Speed * boop::DeltaTime::GetInstance().GetDeltaTime());

	auto newXPos = GetOwner()->GetWorldPosition().x + (moveX);
	auto newYPos = GetOwner()->GetWorldPosition().y + (moveY);

	auto bulletRect = GetOwner()->GetComponent<boop::TextureComponent>()->GetTextureRect();
	bulletRect.x = static_cast<int>(newXPos);
	bulletRect.y = static_cast<int>(newYPos);


	//check if you hit an enemy first
	for (auto& enemy : m_LevelInfo->GetEnemies())
	{
		if (!enemy || enemy->GetOwner()->IsGhost()) continue;
		auto enemyPos = enemy->GetOwner()->GetWorldPosition();
		glm::vec2 enemySize = enemy->GetTankBase()->GetSize();

		SDL_Rect enemyRect{ static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y),
			static_cast<int>(enemySize.x), static_cast<int>(enemySize.y) };

		if (SDL_HasIntersection(&bulletRect, &enemyRect))
		{
			auto levels = boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("level");
			for (auto& level : levels)
			{
				level->GetComponent<Level>()->ResetPlayerCollision(boop::SceneManager::GetInstance().GetActiveScene(), false);
			}
			GetOwner()->SetToDelete(); //delete bullet
			auto enemyDied = enemy->GetOwner()->GetComponent<Health>()->TakeDamage();
			if (enemyDied == 1) m_LevelInfo->GetSubject()->NotifyObserver(boop::Event{ boop::make_sdbm_hash("PlayerKillTank") });
			else if (enemyDied == 2) m_LevelInfo->GetSubject()->NotifyObserver(boop::Event{ boop::make_sdbm_hash("PlayerKillRecognizer") });

			return; // Exit after first collision
		}
	}

	CheckCollisionWall(bulletRect);
	

	GetOwner()->SetLocalPosition(GetOwner()->GetLocalPosition().x + (moveX),
		GetOwner()->GetLocalPosition().y + (moveY));

}

void Bullet::CheckCollisionEnemyBullet()
{
	//with speed
	auto moveX = (m_Dir.x * m_Speed * boop::DeltaTime::GetInstance().GetDeltaTime());
	auto moveY = (m_Dir.y * m_Speed * boop::DeltaTime::GetInstance().GetDeltaTime());

	auto newXPos = GetOwner()->GetWorldPosition().x + (moveX);
	auto newYPos = GetOwner()->GetWorldPosition().y + (moveY);

	auto bulletRect = GetOwner()->GetComponent<boop::TextureComponent>()->GetTextureRect();
	bulletRect.x = static_cast<int>(newXPos);
	bulletRect.y = static_cast<int>(newYPos);


	//check if you hit players
	if (m_Player1)
	{
		auto player1Pos = m_Player1->GetWorldPosition();
		glm::vec2 player1Size = m_Player1->GetComponent<BaseTank>()->GetSize();
		SDL_Rect player1Rect{ static_cast<int>(player1Pos.x), static_cast<int>(player1Pos.y),
			static_cast<int>(player1Size.x), static_cast<int>(player1Size.y) };
		if (SDL_HasIntersection(&bulletRect, &player1Rect))
		{
			//collided with player 1
			m_Player1->GetChildAt(0)->GetComponent<Level>()->CollideWithBullet();
			return; // Exit after first collision
		}
	}
	if (m_Player2 && !m_Player2->ToDelete())
	{
		auto player1Pos = m_Player2->GetWorldPosition();
		glm::vec2 player1Size = m_Player2->GetComponent<BaseTank>()->GetSize();
		SDL_Rect player1Rect{ static_cast<int>(player1Pos.x), static_cast<int>(player1Pos.y),
			static_cast<int>(player1Size.x), static_cast<int>(player1Size.y) };
		if (SDL_HasIntersection(&bulletRect, &player1Rect))
		{
			//collided with player 2
			m_Player2->GetChildAt(0)->GetComponent<Level>()->CollideWithBullet();
			GetOwner()->SetToDelete();
			return; // Exit after first collision
		}
	}

	CheckCollisionWall(bulletRect);


	GetOwner()->SetLocalPosition(GetOwner()->GetLocalPosition().x + (moveX),
		GetOwner()->GetLocalPosition().y + (moveY));
}

void Bullet::CheckCollisionWall(SDL_Rect bullet)
{
	for (auto& collisionObject : m_LevelInfo->GetCollisionObjects())
	{
		if (!collisionObject) continue;
		auto collisionRect = collisionObject->GetComponent<boop::TextureComponent>()->GetTextureRect();


		if (SDL_HasIntersection(&bullet, &collisionRect))
		{
			//collided so change direction -> check which direction was collided

			++m_BounceCount;
			if (m_Dir.x != 0) {
				m_Dir.x = -m_Dir.x; // reverse x direction
			}
			if (m_Dir.y != 0) {
				m_Dir.y = -m_Dir.y; // reverse y direction
			}


			if (m_BounceCount >= 5) //delete after 5 bounces
			{
				GetOwner()->SetToDelete();
			}

			break; // Exit after first collision
		}
	}
}
  