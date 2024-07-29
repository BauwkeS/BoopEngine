#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "HelperFiles/Singleton.h"
#include "Controller.h"
#include "Command.h"

namespace boop
{
	//keystates 
	enum struct keyState
	{
		isDown,		
		isPressed,		
		isUp		
	};

	class InputManager final : public Singleton<InputManager>
	{
	private:
		//map everything up and until in scenes
		//-> in each scene you need different key binds to make sure you dont activate other scenes

		//Controller info
		using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
		using ControllerKeyState = std::pair<ControllerKey, keyState>;
		using ControllerCommandsMap = std::map<ControllerKeyState, std::unique_ptr<Command>>;
		using SceneControllerCommandsMap = std::map<std::string, ControllerCommandsMap>;

		//Keyboard info
		using KeyboardKey = std::pair<SDL_Scancode, keyState>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;
		using SceneKeyboardCommandsMap = std::map<std::string, KeyboardCommandsMap>;

		SceneControllerCommandsMap m_ControllerCommands{};
		SceneKeyboardCommandsMap m_KeyboardCommands{};

		//Controllers for when you have 2 controllers
		std::vector<std::unique_ptr<Controller>> m_Controllers{};

		std::vector<Uint8> m_PreviousKeyState{ std::vector<Uint8>(SDL_NUM_SCANCODES) };
		std::vector<Uint8> m_CurrentPressed{ std::vector<Uint8>(SDL_NUM_SCANCODES) };

	public:
		bool ProcessInput(float deltaTime);
		bool IsKeyPressed(SDL_Scancode keyPressed);

		int AddController();
		// Commands need to be added:
		// - in the correct scene where it works
		// - which controller/keyboard
		// - on what button
		// - in what keystate
		// - the command itself

		void AddCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button, keyState state, std::unique_ptr<Command> pCommand);
		void AddCommand(std::string sceneName, SDL_Scancode key, keyState state, std::unique_ptr<Command> pCommand);
		void RemoveCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button, keyState state);
		void RemoveCommand(std::string sceneName, SDL_Scancode key, keyState state);
	};

}
