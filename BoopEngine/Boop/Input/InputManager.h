#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../HelperFiles/Singleton.h"
#include "Controller.h"
#include "Command.h"
#include "../Scene/SceneManager.h"
#include <SDL.h>

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

		void ExecuteControllerCommands(const std::pair<const ControllerKeyState, std::unique_ptr<Command>>& commandMap,
			const std::unique_ptr<Controller>& controller);

		//Keyboard info
		using KeyboardKey = std::pair<SDL_Scancode, keyState>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;
		using SceneKeyboardCommandsMap = std::map<std::string, KeyboardCommandsMap>;

		void ExecuteKeyboardCommands(const std::pair<const KeyboardKey, std::unique_ptr<Command>>& keyCommand,
			const Uint8* currentKeyState, const std::vector<Uint8>& releasedState);

		SceneControllerCommandsMap m_ControllerCommands{};
		SceneKeyboardCommandsMap m_KeyboardCommands{};
		
		//scene specific commands
		//using InputCommandsMap = std::map<KeyboardCommandsMap, ControllerCommandsMap>;
		//using SceneInputCommandsMap = std::map<std::string, InputCommandsMap>;


		//ControllerCommandsMap m_ControllerCommands{};
		//KeyboardCommandsMap m_KeyboardCommands{};

		//Controllers for when you have 2 controllers
		std::vector<std::unique_ptr<Controller>> m_Controllers{};

		std::vector<Uint8> m_PreviousKeyState{ std::vector<Uint8>(SDL_NUM_SCANCODES) };
		std::vector<Uint8> m_CurrentPressed{ std::vector<Uint8>(SDL_NUM_SCANCODES) };

	//	SceneManager& m_SceneManager{ SceneManager::GetInstance() };

	public:
		bool ProcessInput();
		bool IsKeyPressed(SDL_Scancode keyPressed);

		int AddController();
		int ControllerAmount() const { return static_cast<int>(m_Controllers.size()); }
		void DeleteControllers();

		//only add scene if its in a select scene, otherwise its a global command
		void AddCommand(int controllerIdx, Controller::ControllerButton button, keyState state, std::unique_ptr<Command> pCommand, std::string sceneName="");
		void AddCommand(SDL_Scancode key, keyState state, std::unique_ptr<Command> pCommand, std::string sceneName="");

		void RemoveCommand(int controllerIdx, Controller::ControllerButton button, keyState state, std::string sceneName = "");
		void RemoveCommand(SDL_Scancode key, keyState state, std::string sceneName = "");
		void ClearCommands();
	};

}
