#pragma once
#include <memory>
#include "../../BoopEngine/Boop/GameObject.h"
#include <glm/vec2.hpp>
#include "../../BoopEngine/Boop/Event/Observer.h"
#include "BaseTank.h"

namespace boop {
	class GameObject;
	class Component;
	class Scene;
	class Subject;
}

namespace enemy
{
	//-------------------------------------------------------------------------
	//-------STATES------------------------------------------------------------
	//-------------------------------------------------------------------------
	class BaseState {
	public:
		virtual ~BaseState() = default;
		virtual void Update() = 0;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		BaseState() = default;
		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete; 
	};
}

//-------------------------------------------------------------------------


class Enemy : public boop::Component
	{
	public:
		Enemy(boop::GameObject* owner, int speed, const std::string spritePath);
		~Enemy() = default;

		void FixedUpdate() override;
		void Update() override;
		void Render() const override;

		BaseTank* GetTankBase() const { return m_pTankBase; }

	private:
		BaseTank* m_pTankBase{}; 

		void SeePlayer(boop::GameObject* player);
	};


//-------------------------------------------------------------------------
//--------ENEMIES----------------------------------------------------------
//-------------------------------------------------------------------------

class BlueTankEnemy : public Enemy
{
public:
	BlueTankEnemy(boop::GameObject* owner, int speed, const std::string spritePath)
		: Enemy(owner, speed, spritePath) {
	}
	//void Update() override;
	//void OnEnter();
	//void OnExit();
private:
	std::unique_ptr<enemy::BaseState> m_pCurrentState;
};