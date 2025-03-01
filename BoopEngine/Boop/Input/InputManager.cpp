#include <SDL.h>
#include "InputManager.h"

#include "../Scene/Scene.h"
#include "backends/imgui_impl_sdl2.h"

namespace boop
{
	bool InputManager::ProcessInput(float deltaTime)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) {
				return false;
			}

			//process event for IMGUI
			ImGui_ImplSDL2_ProcessEvent(&e);
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
		std::string sceneName = m_SceneManager.GetActiveScene()->GetName();


		m_CurrentPressed = currentPressed;
		m_PreviousKeyState = previousState;

		//--
		//EXECUTE KEYBOARD
		//go over the keyboard commands
		//go over the keystate
		//if keystate is the same, then execute

		for (const auto& [keyStatePair, command] : m_KeyboardCommands[sceneName])
		{
			// Decompose the keyStatePair into key and state
			const auto& [key, state] = keyStatePair;

			// Determine if the key is currently pressed and if the expected state is 'isDown'
			bool isKeyDown = IsKeyPressed(key) && (state == keyState::isDown);

			// Determine if the key is held down and if the expected state is 'isPressed'
			bool isKeyHeld = currentKeyState[key] && (state == keyState::isPressed);

			// Determine if the key has been released and if the expected state is 'isUp'
			bool isKeyUp = releasedState[key] && (state == keyState::isUp);

			// Execute the command if any of the conditions (isKeyDown, isKeyHeld, or isKeyUp) are true
			if (isKeyDown || isKeyHeld || isKeyUp)
			{
				command->Execute(deltaTime); // Execute the command with the elapsed time as an argument
			}
		}

		for (const auto& controller : m_Controllers)
		{
			controller->Update();

			for (const auto& command : m_ControllerCommands[sceneName])
			{
				auto [controllerIdx, cButton] = command.first.first;

				if (controllerIdx == controller->GetId())
				{
					bool shouldExecute = false; // Flag to determine if the command should be executed

					// Determine if the command should execute based on the key state
					switch (command.first.second) //the key state
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
						command.second->Execute(deltaTime);
					}
				}
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

	//--COMMANDS

	void InputManager::AddCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button,
	                              keyState state, std::unique_ptr<Command> pCommand)
	{
		//make a controller key and then add it to the commands in the correct scene

		ControllerKey cKey = std::make_pair(controllerIdx, button);
		ControllerKeyState cKeyState = std::make_pair(cKey, state);
		// Insert the command into the controller commands map for the active scene
		m_ControllerCommands[sceneName].insert(std::make_pair(cKeyState, std::move(pCommand)));

		//use std::move to efficiently transfer ownership of pCommand into the map without copying it, ensuring optimal performance
	}

	void InputManager::AddCommand(std::string sceneName, SDL_Scancode key, keyState state,
		std::unique_ptr<Command> pCommand)
	{
		//make a keyboard key and then add it to the commands in the correct scene

		KeyboardKey kKey = std::make_pair(key, state);
		m_KeyboardCommands[sceneName].insert(std::make_pair(kKey, std::move(pCommand)));
	}

	void InputManager::RemoveCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button,
		keyState state)
	{
		//make a controller key and then erase it from the commands
		ControllerKey cKey = std::make_pair(controllerIdx, button);
		ControllerKeyState cKeyState = std::make_pair(cKey, state);
		m_ControllerCommands[sceneName].erase(cKeyState);
	}

	void InputManager::RemoveCommand(std::string sceneName, SDL_Scancode key, keyState state)
	{
		//make a keyboard key and then erase it from the commands
		KeyboardKey kKey = std::make_pair(key, state);
		m_KeyboardCommands[sceneName].erase(kKey);
	}
}
