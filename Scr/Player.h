#pragma once
#include <memory>

#include "../BoopEngine/Boop/Components/Component.h"
#include "States.h"

namespace boop {
	class GameObject;
}

namespace booble
{
	class Player : public boop::Component
	{
	public:
		Player(boop::GameObject* owner);


		void FixedUpdate(float deltaTime) override;
		void Update(float deltaTime) override;
		void LateUpdate(float deltaTime) override;
		void Render() const override;

		std::unique_ptr<Component> Clone() const override;

		PlayerStateMachine* GetStateMachine() { return m_StateMachine.get(); }
	private:
		std::unique_ptr<PlayerStateMachine> m_StateMachine;
	};

}