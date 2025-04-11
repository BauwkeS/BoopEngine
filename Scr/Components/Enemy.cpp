#include "Enemy.h"

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
#include "ScoreObserver.h"


Enemy::Enemy(boop::GameObject* owner, int speed, const std::string spritePath)
	: Component(owner)
{
	//add base tank
	m_pTankBase = owner->AddComponent<BaseTank>(speed, spritePath);

}

void Enemy::FixedUpdate()
{
}

void Enemy::Update()
{

}

void Enemy::Render() const
{
}