#include "Bullet.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"
#include "../../BoopEngine/Boop/DeltaTime.h"

Bullet::Bullet(boop::GameObject* owner, glm::vec2 dir, std::vector<boop::GameObject*> collision)
	: Component(owner), m_Dir{ dir }, m_CollisionObjects{ collision }
{
	//add sprite
	//owner->AddComponent< boop::TextureComponent>(static_cast<std::string>(spritePath));

}

void Bullet::FixedUpdate()
{
}

void Bullet::Update()
{
	//
	//m_Dir.x = m_Dir.x + (m_Dir.x * boop::DeltaTime::GetInstance().GetDeltaTime());
	//m_Dir.y = m_Dir.y + (m_Dir.y * boop::DeltaTime::GetInstance().GetDeltaTime());
	//GetOwner()->SetLocalPosition(newXPos, newYPos);
	
	CheckCollision();
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

	for (auto& collisionObject : m_CollisionObjects)
	{
		if (!collisionObject) continue;
		auto collisionRect = collisionObject->GetComponent<boop::TextureComponent>()->GetTextureRect();
		auto bulletRect = GetOwner()->GetComponent<boop::TextureComponent>()->GetTextureRect();
		bulletRect.x = static_cast<int>(newXPos);
		bulletRect.y = static_cast<int>(newYPos);
		

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

		//check for x rect and y rect seperately to reflect correctly on the map?


		

	}

	GetOwner()->SetLocalPosition(GetOwner()->GetLocalPosition().x + (moveX),
		GetOwner()->GetLocalPosition().y + (moveY));

}
  