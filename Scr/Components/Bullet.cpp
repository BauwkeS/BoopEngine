#include "Bullet.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"

Bullet::Bullet(boop::GameObject* owner, const std::string& spritePath, glm::vec2 speed)
	: Component(owner), m_Speed{ speed }
{
	//add sprite
	owner->AddComponent< boop::TextureComponent>(static_cast<std::string>(spritePath));

}

void Bullet::FixedUpdate()
{
}

void Bullet::Update()
{
}

void Bullet::Render() const
{
}
