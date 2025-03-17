#include "../BoopEngine/Boop/HelperFiles/Singleton.h"
#include <memory>
#include <string>

namespace boop {
	class GameObject;
}

namespace booble
{
	class GameLoader final : public boop::Singleton<GameLoader>
	{
	private:
		std::unique_ptr<boop::GameObject> CreateAir();
		std::unique_ptr<boop::GameObject> CreateWall(int whichBlock);
		std::unique_ptr<boop::GameObject> CreatePlatform(int whichBlock);

		std::unique_ptr<boop::GameObject> CreatePlayerOne(const std::string spritePath, const std::string tagName, int playerSpeed );
		std::unique_ptr<boop::GameObject> CreatePlayerTwo(const std::string spritePath, const std::string tagName, int playerSpeed );

		const std::string m_LevelOne = "LevelOne";
		void MakeLevelOne();
	public:
		void MakeGame();
	};
}