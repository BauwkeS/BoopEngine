#include "BaseTank.h"

#include <mutex>

#include "../../BoopEngine/Boop/Components/Component.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../../BoopEngine/Boop/Scene/Scene.h"
#include "../../BoopEngine/Boop/Input/InputManager.h"
#include "../GameCommands.h"
#include "Events.h"
#include "../../BoopEngine/Boop/Event/Subject.h"
#include "../../BoopEngine/Boop/Components/TextureComponent.h"
#include "HealthObserver.h"

BaseTank::BaseTank(boop::GameObject* owner, int speed, const std::string spritePath)
	: Component(owner), m_Speed{ speed }
{
	//add sprite
	auto sprite = owner->AddComponent< boop::TextureComponent>(static_cast<std::string>(spritePath),1.75f);
	m_Size = sprite->GetSize();


	//add health
	owner->AddComponent<Health>(4);
}

void BaseTank::ResetPosition()
{
	GetOwner()->SetLocalPosition(m_StartPos.x, m_StartPos.y);
}

void BaseTank::FixedUpdate()
{
}

void BaseTank::Update()
{

}

void BaseTank::Render() const
{
}
