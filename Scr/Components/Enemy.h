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
		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete; 
		virtual std::unique_ptr<BaseState>HandleState() { return nullptr; };

	protected:
		Enemy* m_pOwner{}; 
		BaseState(Enemy* owner) : m_pOwner(owner) {}
	};

	class GoToClosestPlayer : public BaseState
	{
	public:
		GoToClosestPlayer(Enemy* owner);
		~GoToClosestPlayer() = default;
		void Update() override;
		void OnEnter() override;
		void OnExit() override;
		std::unique_ptr<BaseState>HandleState() override;
	private:
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
		Enemy(boop::GameObject* owner);
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

		void UpdateFromScene();

		void HandleStateChanges()
		{
			if (m_pCurrentState)
			{
				auto newState = m_pCurrentState->HandleState();
				if (newState)
				{
					m_pCurrentState->OnExit();
					m_pCurrentState = std::move(newState);
					m_pCurrentState->OnEnter();
				}
			}
		}

		//check functions
		glm::vec2 SeePlayer();
		void MoveToPos(glm::vec2 movePos);
		bool CollideWithWall();


		boop::GameObject* GetPlayer1() const { return m_Player1; }
		boop::GameObject* GetPlayer2() const { return m_Player2; }

	protected:

		BaseTank* m_pTankBase{}; 
		std::unique_ptr<enemy::BaseState> m_pCurrentState;

		
	private:
		bool CheckWallInBetween(glm::vec2 pos, bool horizontal);
		glm::vec2 CheckPlayerPosSeen(glm::vec2 playerPos);

		//player stuff
		boop::GameObject* m_Player1{};
		boop::GameObject* m_Player2{};

		std::vector<boop::GameObject*> m_CollisionObjects{};

	};


//-------------------------------------------------------------------------
//--------ENEMIES----------------------------------------------------------
//-------------------------------------------------------------------------

class BlueTankEnemy : public Enemy
{
public:
	BlueTankEnemy(boop::GameObject* owner)
		: Enemy(owner) {
		//set base state to use
		//GoToState(std::make_unique<enemy::GoToClosestPlayer>(this));
		m_pCurrentState = std::make_unique<enemy::GoToClosestPlayer>(this);
	}
private:
	// Add any specific functionality for BlueTankEnemy here
	float m_CooldownShoot{ 0.f }; // Cooldown for shooting
	
};

class RecognizerEnemy : public Enemy
{
public:
	RecognizerEnemy(boop::GameObject* owner)
		: Enemy(owner) {
		//set base state to use
		//GoToState(std::make_unique<enemy::GoToClosestPlayer>(this));
		m_pCurrentState = std::make_unique<enemy::GoToClosestPlayer>(this);
	}
	//private:
		// Add any specific functionality for BlueTankEnemy here
};