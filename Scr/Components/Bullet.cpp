#include "Bullet.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"
#include "../../BoopEngine/Boop/DeltaTime.h"

Bullet::Bullet(boop::GameObject* owner, const std::string&, glm::vec2 dir)
	: Component(owner), m_Dir{ dir }
{
	//add sprite
	//owner->AddComponent< boop::TextureComponent>(static_cast<std::string>(spritePath));

}

void Bullet::FixedUpdate()
{
}

void Bullet::Update()
{
	auto newXPos = GetOwner()->GetLocalPosition().x + (m_Dir.x * boop::DeltaTime::GetInstance().GetDeltaTime());
	auto newYPos = GetOwner()->GetLocalPosition().y + (m_Dir.y * boop::DeltaTime::GetInstance().GetDeltaTime());
	GetOwner()->SetLocalPosition(newXPos, newYPos);
	//
	//m_Dir.x = m_Dir.x + (m_Dir.x * boop::DeltaTime::GetInstance().GetDeltaTime());
	//m_Dir.y = m_Dir.y + (m_Dir.y * boop::DeltaTime::GetInstance().GetDeltaTime());
	//GetOwner()->SetLocalPosition(newXPos, newYPos);
	

}

void Bullet::Render() const
{

}
