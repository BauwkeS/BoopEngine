#pragma once
#include "../BoopEngine/Boop/HelperFiles/Singleton.h"
#include "../BoopEngine/Boop/Scene/GameObjectType.h"
#include <memory>
#include <string>
#include "Components/LevelObserver.h"

namespace boop {
	class GameObject;
	class Scene;
}

namespace booble
{
	enum class GameMode {
		SINGLEPLAYER,
		MULTIPLAYER,
		COOP
	};

	class GameLoader final : public boop::Singleton<GameLoader>
	{
	private:
		//Register GameObject types
		void RegisterGameObjectTypes();
		void RegisterAirType();
		void RegisterWallType();
		void RegisterWallBorderType();
		void RegisterPlayerType(const std::string& spritePath, const std::string& tagName, int playerSpeed);
		void RegisterRecognizerEnemy(const std::string& spritePath, const std::string& tagName, int playerSpeed);
		void RegisterBlueTankEnemy(const std::string& spritePath, const std::string& tagName, int playerSpeed);


		//Level
		void MakeLevel(const std::string& levelPath, const std::string& levelName);
		void MakeMainScreen();
		void MakeEndingScreen();
		
		int m_selectedGamemode{};

		std::unique_ptr<LevelObserver> m_levelObserver{};

	public:
		void MakeGame();
		void InitializeLevels();

		void SetSelectedGamemode(int gamemode) { m_selectedGamemode = gamemode; }
		int GetSelectedGamemode() const { return m_selectedGamemode; }
	};
}