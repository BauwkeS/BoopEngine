#include "Bullet.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"
#include "../../BoopEngine/Boop/DeltaTime.h"
#include "Enemy.h"
#include "../Level.h"
#include "Player.h"

Bullet::Bullet(boop::GameObject* owner, glm::vec2 dir, Level* levelinfo)
	: Component(owner), m_Dir{ dir }, m_LevelInfo{ levelinfo }
{
	//add sprite
	//owner->AddComponent< boop::TextureComponent>(static_cast<std::string>(spritePath));
	//m_CollisionObjects = m_LevelInfo->GetCollisionObjects();
	//m_Enemies = m_LevelInfo->GetEnemies();
}

void Bullet::FixedUpdate()
{
	CheckCollision();
}

void Bullet::Update()
{
	//
	//m_Dir.x = m_Dir.x + (m_Dir.x * boop::DeltaTime::GetInstance().GetDeltaTime());
	//m_Dir.y = m_Dir.y + (m_Dir.y * boop::DeltaTime::GetInstance().GetDeltaTime());
	//GetOwner()->SetLocalPosition(newXPos, newYPos);
	
	
}

void Bullet::Render() const
{

}

void Bullet::CheckCollision()
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
		if (!enemy) continue;
		auto enemyPos = enemy->GetOwner()->GetWorldPosition();
		glm::vec2 enemySize = enemy->GetTankBase()->GetSize();

		SDL_Rect enemyRect{ static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y),
			static_cast<int>(enemySize.x), static_cast<int>(enemySize.y) };

		if (SDL_HasIntersection(&bulletRect, &enemyRect))
		{
			//collided with enemy
			//booble::Player* player = m_LevelInfo->GetOwner()->GetParent()->GetComponent<booble::Player>();
			//if (!player) return; // no player found, exit
			//player->GetSubject()->NotifyObserver(boop::Event{ boop::make_sdbm_hash("PlayerKillTank") });


			//player->Onn(boop::Event{ boop::make_sdbm_hash("PlayerKillEnemy") });
			m_LevelInfo->GetSubject()->NotifyObserver(boop::Event{ boop::make_sdbm_hash("PlayerKillTank") });

			//m_LevelInfo->SetHitTank();


			//m_LevelInfo->get

			GetOwner()->SetToDelete();
			enemy->GetOwner()->SetToDelete(); //delete the enemy
			//m_LevelInfo->ResetPlayerCollision(boop::SceneManager::GetInstance().GetActiveScene());

			auto levels = boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("level");
			for (auto& level : levels)
			{
				level->GetComponent<Level>()->ResetPlayerCollision(boop::SceneManager::GetInstance().GetActiveScene());
			}

			//m_Enemies = m_LevelInfo->GetEnemies();
			return; // Exit after first collision
		}
	}


	for (auto& collisionObject : m_LevelInfo->GetCollisionObjects())
	{
		if (!collisionObject) continue;
		auto collisionRect = collisionObject->GetComponent<boop::TextureComponent>()->GetTextureRect();
		

		if (SDL_HasIntersection(&bulletRect, &collisionRect))
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

	GetOwner()->SetLocalPosition(GetOwner()->GetLocalPosition().x + (moveX),
		GetOwner()->GetLocalPosition().y + (moveY));

}
  