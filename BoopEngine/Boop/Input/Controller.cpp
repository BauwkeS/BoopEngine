#include "Controller.h"
#include <Windows.h>
#include <Xinput.h>

//has:
// - the previous state + current state (of both XINPUT and WORD)
// -> this is to check if it has changed from before 
// - code from ppt


namespace boop
{
	//CONTROLLER PIMPL IMPLEMENTATION

	class Controller::ControllerImpl final
	{
	private:
		
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};

		WORD m_ButtonsPressedThisFrame{};
		WORD m_ButtonsReleasedThisFrame{};

		//which controller
		unsigned int m_ControllerId{};

	public:

		ControllerImpl(unsigned int controllerId)
			: m_ControllerId(controllerId)
		{
			ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		}

		//process input every frame via 'polling' -> from ppt
		void Update()
		{
			//copy current state to previous one
			CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
			//empty current state
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
			//get the current state
			XInputGetState(m_ControllerId, &m_CurrentState);

			//check if state changed
			auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
			m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		}

		//Keystate functions
		bool IsDownThisFrame(unsigned int button) const
		{
			return m_ButtonsPressedThisFrame & button;
		}
		bool IsUpThisFrame(unsigned int button) const
		{
			return m_ButtonsReleasedThisFrame & button;
		}
		bool IsPressed(unsigned int button) const
		{
			return m_CurrentState.Gamepad.wButtons & button;
		}

		//getter
		unsigned int GetId() { return m_ControllerId; }
	};

	//CPP FOR PIMPL

	Controller::Controller(unsigned int controllerId)
	{
		pImpl = new ControllerImpl{ controllerId };
	}


	Controller::~Controller()
	{
		delete pImpl;
		pImpl = nullptr;
	}


	void Controller::Update()
	{
		pImpl->Update();
	}

	//getter 
	unsigned int Controller::GetId() const
	{
		return pImpl->GetId();
	}

	//Keystate functions

	bool Controller::IsDownThisFrame(ControllerButton button) const
	{
		return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsUpThisFrame(ControllerButton button) const
	{
		return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsPressed(ControllerButton button) const
	{
		return pImpl->IsPressed(static_cast<unsigned int>(button));
	}
}
