#pragma once
namespace boop
{
	class GameObject;

	class BaseState
	{
	public:
		virtual ~BaseState()=default;

		virtual void Update(float deltaTime) = 0;

		virtual void OnEnter()=0;
		virtual void OnExit()=0;

		//rule of 5
		BaseState() = default;
		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete;
	};

	class StateMachine
	{
	public:

		virtual void GoToState(BaseState* newState)
		{
			if (newState)
			{
				if (m_pState)
				{
					m_pState->OnExit();
					delete m_pState;
				}
				m_pState = newState;
				m_pState->OnEnter();
			}
		}

		StateMachine(GameObject* owner, BaseState* state)
			: m_pOwner{ owner },
			m_pState{ state } {}

		virtual ~StateMachine() = default;
		//rule of 5
		StateMachine(const StateMachine& other) = delete;
		StateMachine(StateMachine&& other) = delete;
		StateMachine& operator=(const StateMachine& other) = delete;
		StateMachine& operator=(StateMachine&& other) = delete;

	protected:
		BaseState* m_pState{};
		GameObject* m_pOwner{};
	};
}
