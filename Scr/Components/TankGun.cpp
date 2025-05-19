#include "TankGun.h"
#include "../../BoopEngine/Boop/GameObject.h" 
#include "../../BoopEngine/Boop/Components/TextureComponent.h"

TankGun::TankGun(boop::GameObject* owner, const std::string spritePath)
	: Component(owner)
{
	owner->AddComponent< boop::TextureComponent>(static_cast<std::string>(spritePath));

}

void TankGun::FixedUpdate()
{
}

void TankGun::Update()
{
}

void TankGun::Render() const
{
}
