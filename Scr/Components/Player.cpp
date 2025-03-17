#include "Player.h"

#include <mutex>

#include "../../BoopEngine/Boop/Components/Component.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../../BoopEngine/Boop/Scene/Scene.h"
#include "../../BoopEngine/Boop/Input/InputManager.h"
#include "../GameCommands.h"
#include "Events.h"


namespace booble
{
	Player::Player(boop::GameObject* owner, float speed)
		: Component(owner), Observer(), Subject(), m_Speed{speed}
	{
	}

	void Player::FixedUpdate()
	{
	}

	void Player::Update()
	{

	}

	void Player::Render() const
	{
	}

	void Player::OnNotify(boop::Event& event)
	{
		if (dynamic_cast<PlayerKillTank*>(&event)) {
			m_Score += 100;
			PlayerKillTank playerKillTank{};
			NotifyObserver(playerKillTank);
		}
		if (dynamic_cast<PlayerKillRecognizer*>(&event)) {
			m_Score += 250;
			PlayerKillRecognizer plr{};
			NotifyObserver(plr);
		}
	}
}
	