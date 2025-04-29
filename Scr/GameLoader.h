#pragma once
#include "../BoopEngine/Boop/HelperFiles/Singleton.h"
#include "../BoopEngine/Boop/Scene/GameObjectType.h"
#include <memory>
#include <string>

namespace boop {
	class GameObject;
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
		void RegisterEnemyType(const std::string& spritePath, const std::string& tagName, int playerSpeed);


		//Level
		void MakeLevelOne();
		void MakeLevelTwo();
		void MakeMainScreen();
		
		int m_selectedGamemode{};
	public:
		void MakeGame();
		void InitializeLevels();

		void SetSelectedGamemode(int gamemode) { m_selectedGamemode = gamemode; }
		int GetSelectedGamemode() const { return m_selectedGamemode; }
	};
}