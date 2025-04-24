#include <SDL.h>
#include "InputManager.h"

#include "../Scene/Scene.h"

namespace boop
{
	void InputManager::ExecuteControllerCommands(const std::pair<const ControllerKeyState, std::unique_ptr<Command>>& commandMap,
		const std::unique_ptr<Controller>& controller)
	{
		auto [controllerIdx, cButton] = commandMap.first.first;

		if (controllerIdx == controller->GetId())
		{
			bool shouldExecute = false; // Flag to determine if the command should be executed

			// Determine if the command should execute based on the key state
			switch (commandMap.first.second) //the key state
			{
			case keyState::isDown:
				// Check if the key is pressed down in the current frame
				shouldExecute = controller->IsDownThisFrame(cButton);
				break;
			case keyState::isPressed:
				// Check if the key is pressed continuously (held down)
				shouldExecute = controller->IsPressed(cButton);
				break;
			case keyState::isUp:
				// Check if the key is released in the current frame
				shouldExecute = controller->IsUpThisFrame(cButton);
				break;
			}

			// If the conditions for executing the command are met, perform the action
			if (shouldExecute)
			{
				// Execute the command with the elapsed time as an argument
				commandMap.second->Execute();
			}
		}
	}

	void InputManager::ExecuteKeyboardCommands(const std::pair<const KeyboardKey, std::unique_ptr<Command>>& keyCommand, const Uint8* currentKeyState, const std::vector<Uint8>& releasedState)
	{

		//// Decompose the keyStatePair into key and state
		//const auto& [key, state] = keyStatePair;

		//// Determine if the key is currently pressed and if the expected state is 'isDown'
		//bool isKeyDown = IsKeyPressed(key) && (state == keyState::isDown);

		//// Determine if the key is held down and if the expected state is 'isPressed'
		//bool isKeyHeld = currentKeyState[key] && (state == keyState::isPressed);

		//// Determine if the key has been released and if the expected state is 'isUp'
		//bool isKeyUp = releasedState[key] && (state == keyState::isUp);

		//// Execute the command if any of the conditions (isKeyDown, isKeyHeld, or isKeyUp) are true
		//if (isKeyDown || isKeyHeld || isKeyUp)
		//{
		//	command->Execute(); // Execute the command with the elapsed time as an argument
		//}
		//--

		const auto& [key, state] = keyCommand.first;

		bool shouldExecute = false;
		switch (state) {
		case keyState::isDown:
			shouldExecute = IsKeyPressed(key);
			break;
		case keyState::isPressed:
			shouldExecute = currentKeyState[key];
			break;
		case keyState::isUp:
			shouldExecute = releasedState[key];
			break;
		}

		if (shouldExecute) {
			keyCommand.second->Execute();
		}
	}


	bool InputManager::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) {
				return false;
			}
		}

		//--
		//leave the lots of comments because I find this difficult


		//you will need:
		// - current keyboard state
		// - current key state (best in std::vector<Uint8>)
		// - previous key state (best in std::vector<Uint8>)
		// - my released state -> which was released this frame

		// Get the current state of the keyboard
		int keyStateSize{};
		const Uint8* currentKeyState = SDL_GetKeyboardState(&keyStateSize);

		// Store the current keyboard state in a vector
		std::vector<Uint8> currentState(currentKeyState, currentKeyState + keyStateSize);

		// Store the previous keyboard state in a vector
		std::vector<Uint8> previousState(m_PreviousKeyState.begin(), m_PreviousKeyState.end());

		// Initialize vectors for tracking state changes and released keys
		std::vector<Uint8> changedState(currentState.size());
		std::vector<Uint8> releasedState(currentState.size());
		std::vector<Uint8> currentPressed(currentState.size());

		// Calculate the state changes (pressed or released keys) using bitwise XOR
		for (size_t i = 0; i < currentState.size(); ++i) {
			changedState[i] = currentState[i] ^ previousState[i];
		}

		// Identify keys that are currently pressed and have changed state
		for (size_t i = 0; i < currentState.size(); ++i) {
			currentPressed[i] = currentState[i] & changedState[i];
		}

		// Identify keys that have been released in the current frame
		for (size_t i = 0; i < currentState.size(); ++i) {
			releasedState[i] = changedState[i] & (~currentState[i]);
		}

		// Retrieve the name of the active scene
		std::string sceneName = boop::SceneManager::GetInstance().GetActiveScene()->GetName();


		m_CurrentPressed = currentPressed;
		m_PreviousKeyState = previousState;

		//--
		//EXECUTE KEYBOARD
		//go over the keyboard commands
		//go over the keystate
		//if keystate is the same, then execute

		for (const auto& keyCommand : m_KeyboardCommands[""])
		{
			// Decompose the keyStatePair into key and state
			//const auto& [key, state] = keyStatePair;

			// Determine if the key is currently pressed and if the expected state is 'isDown'
			//bool isKeyDown = IsKeyPressed(key) && (state == keyState::isDown);

			// Determine if the key is held down and if the expected state is 'isPressed'
			//bool isKeyHeld = currentKeyState[key] && (state == keyState::isPressed);

			// Determine if the key has been released and if the expected state is 'isUp'
			//bool isKeyUp = releasedState[key] && (state == keyState::isUp);

			// Execute the command if any of the conditions (isKeyDown, isKeyHeld, or isKeyUp) are true
			//if (isKeyDown || isKeyHeld || isKeyUp)
			//{
			//	command->Execute(); // Execute the command with the elapsed time as an argument
			//}
			ExecuteKeyboardCommands(keyCommand, currentKeyState, releasedState);
		}


		for (const auto& keyCommand : m_KeyboardCommands[sceneName])  //check for scene only commands too
		{
			ExecuteKeyboardCommands(keyCommand, currentKeyState, releasedState); 
		}

		for (const auto& controller : m_Controllers)
		{
			controller->Update();

			for (const auto& command : m_ControllerCommands[""])
			{
				//auto [controllerIdx, cButton] = command.first.first;

				//if (controllerIdx == controller->GetId())
				//{
				//	bool shouldExecute = false; // Flag to determine if the command should be executed

				//	// Determine if the command should execute based on the key state
				//	switch (command.first.second) //the key state
				//	{
				//	case keyState::isDown:
				//		// Check if the key is pressed down in the current frame
				//		shouldExecute = controller->IsDownThisFrame(cButton);
				//		break;
				//	case keyState::isPressed:
				//		// Check if the key is pressed continuously (held down)
				//		shouldExecute = controller->IsPressed(cButton);
				//		break;
				//	case keyState::isUp:
				//		// Check if the key is released in the current frame
				//		shouldExecute = controller->IsUpThisFrame(cButton);
				//		break;
				//	}

				//	// If the conditions for executing the command are met, perform the action
				//	if (shouldExecute)
				//	{
				//		// Execute the command with the elapsed time as an argument
				//		command.second->Execute();
				//	}
				//}
				ExecuteControllerCommands(command, controller);
			}
			for (const auto& command : m_ControllerCommands[sceneName]) //check for scene only commands too
			{
				ExecuteControllerCommands(command, controller);
			}
		}

		//EXECUTE CONTROLLERS
		//go over all controllers
		//update the controller buttons
		//then do same as the keyboard
		//--

		//update previous key state to current
		m_PreviousKeyState = currentState;


		//--
		return true;

	}

	bool InputManager::IsKeyPressed(SDL_Scancode keyPressed)
	{
		//check if the key you pressed is the current key
		if (m_CurrentPressed[keyPressed]) return true;
		return false;
	}

	int InputManager::AddController()
	{
		//maybe someday make a failsafe to not make more than 2 controllers
		//add a controller to the list + return the index of the new controller made
		m_Controllers.emplace_back(std::make_unique<Controller>(static_cast<int>(m_Controllers.size())));
		return static_cast<int>(m_Controllers.size());
	}

	void InputManager::DeleteControllers()
	{
		//delete all controllers
		for (auto& controller : m_Controllers)
		{
			controller.reset();
		}
		m_Controllers.clear();
	}

	//--COMMANDS

	void InputManager::AddCommand(int controllerIdx, Controller::ControllerButton button,
	                              keyState state, std::unique_ptr<Command> pCommand, std::string sceneName)
	{
		//make a controller key and then add it to the commands in the correct scene

		ControllerKey cKey = std::make_pair(controllerIdx, button);
		ControllerKeyState cKeyState = std::make_pair(cKey, state);
		// Insert the command into the controller commands map for the active scene
		 m_ControllerCommands[sceneName].insert(std::make_pair(cKeyState, std::move(pCommand)));
		//use std::move to efficiently transfer ownership of pCommand into the map without copying it, ensuring optimal performance
	}

	void InputManager::AddCommand(SDL_Scancode key, keyState state,
		std::unique_ptr<Command> pCommand, std::string sceneName)
	{
		//make a keyboard key and then add it to the commands in the correct scene

		KeyboardKey kKey = std::make_pair(key, state);
		m_KeyboardCommands[sceneName].insert(std::make_pair(kKey, std::move(pCommand)));
	}

	void InputManager::RemoveCommand(int controllerIdx, Controller::ControllerButton button,
		keyState state, std::string sceneName)
	{
		//make a controller key and then erase it from the commands
		ControllerKey cKey = std::make_pair(controllerIdx, button);
		ControllerKeyState cKeyState = std::make_pair(cKey, state);
		m_ControllerCommands[sceneName].erase(cKeyState);
	}

	void InputManager::RemoveCommand(SDL_Scancode key, keyState state, std::string sceneName)
	{
		//make a keyboard key and then erase it from the commands
		KeyboardKey kKey = std::make_pair(key, state);
		m_KeyboardCommands[sceneName].erase(kKey);
	}
	void InputManager::ClearCommands()
	{
		//clear all commands
		//for (auto& controller : m_ControllerCommands)
		//{
		//	controller.second.reset();
		//}
		//for (auto& controller : m_KeyboardCommands)
		//{
		//	controller.second.reset();
		//}
		m_ControllerCommands.clear();
		m_KeyboardCommands.clear();
	}
}
