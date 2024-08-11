#pragma once
#include <memory>

namespace boop {
	class GameObject;
}
namespace booble
{

	class LevelComponents final
	{
	public:
		static std::unique_ptr<boop::GameObject> CreateAir();
		//0 for pruple ; 1 for rock
		static std::unique_ptr<boop::GameObject> CreateWall(int whichBlock);
		static std::unique_ptr<boop::GameObject> CreatePlatform(int whichBlock);

		static std::unique_ptr<boop::GameObject> CreatePlayer();
	};

}