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
		static std::unique_ptr<boop::GameObject> CreateAir();
		//0 for pruple ; 1 for rock
		static std::unique_ptr<boop::GameObject> CreateWall(int whichBlock);
		static std::unique_ptr<boop::GameObject> CreatePlatform(int whichBlock);

		static std::unique_ptr<boop::GameObject> CreatePlayer(const std::string spritePath, const std::string tagName);

	public:
		void MakeGame();
	};
}