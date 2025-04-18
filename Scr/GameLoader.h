#pragma once
#include "../BoopEngine/Boop/HelperFiles/Singleton.h"
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
		std::unique_ptr<boop::GameObject> CreateAir();
		std::unique_ptr<boop::GameObject> CreateWall(int whichBlock);
		std::unique_ptr<boop::GameObject> CreatePlatform(int whichBlock);
		std::unique_ptr<boop::GameObject> CreatePlayer(const std::string spritePath, const std::string tagName, int playerSpeed );
		std::unique_ptr<boop::GameObject> CreateEnemy(const std::string spritePath, const std::string tagName, int playerSpeed );

		//Level
		void MakeLevelOne();
		void MakeMainScreen();
		
		int m_selectedGamemode{};
	public:
		void MakeGame();
		void InitializeLevels();

		void SetSelectedGamemode(int gamemode) { m_selectedGamemode = gamemode; }
		int GetSelectedGamemode() const { return m_selectedGamemode; }
	};
}