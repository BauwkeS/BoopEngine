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

class Enemy;

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
	//	BaseState() = default;
		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete; 

	protected:
		Enemy* m_pOwner{}; // Pointer to the owner GameObject
		BaseState(Enemy* owner) : m_pOwner(owner) {} // Constructor to set owner
	};

	class GoToClosestPlayer : public BaseState
	{
	public:
		GoToClosestPlayer(Enemy* owner);
		~GoToClosestPlayer() = default;
		void Update() override;
		void OnEnter() override;
		void OnExit() override;
	private:
		//player stuff
		boop::GameObject* m_Player1{};
		boop::GameObject* m_Player2{};

		std::vector<boop::GameObject*> m_CollisionObjects{};

		glm::vec2 m_TargetPosition{ 0,0 }; // Target position to move towards
		glm::vec2 FindPlayer();
	};

	/*class Shoot : public BaseState
	{
	public:
		Shoot(Enemy* owner);
		~Shoot() = default;
		void Update() override;
		void OnEnter() override;
		void OnExit() override;
	};

	class Die : public BaseState
	{
	public:
		Die(Enemy* owner);
		~Die() = default;
		void Update() override;
		void OnEnter() override;
		void OnExit() override;
	};*/
}

//-------------------------------------------------------------------------
//--------ENEMY-BASE-------------------------------------------------------
//-------------------------------------------------------------------------

class Enemy : public boop::Component
	{
	public:
		Enemy(boop::GameObject* owner, int speed, const std::string spritePath);
		~Enemy() = default;

		void FixedUpdate() override;
		void Update() override;
		void Render() const override;

		//rule of 5
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		BaseTank* GetTankBase() const { return m_pTankBase; }

		virtual void GoToState(std::unique_ptr<enemy::BaseState> newState) 
		{
			if (newState)
			{
				if (m_pCurrentState)
				{
					m_pCurrentState->OnExit();
				}
				m_pCurrentState = std::move(newState);
				m_pCurrentState->OnEnter();
			}
		}

		glm::vec2 SeePlayer();
	protected:
		BaseTank* m_pTankBase{}; 
		std::unique_ptr<enemy::BaseState> m_pCurrentState;
		void MoveToPos(glm::vec2 movePos);

		
	private:
		glm::vec2 CheckPlayerPosSeen(glm::vec2 playerPos);

	};


//-------------------------------------------------------------------------
//--------ENEMIES----------------------------------------------------------
//-------------------------------------------------------------------------

class BlueTankEnemy : public Enemy
{
public:
	BlueTankEnemy(boop::GameObject* owner, int speed, const std::string spritePath)
		: Enemy(owner, speed, spritePath) {
		//set base state to use
		GoToState(std::make_unique<enemy::GoToClosestPlayer>(this));
	}
private:
	// Add any specific functionality for BlueTankEnemy here
	
};