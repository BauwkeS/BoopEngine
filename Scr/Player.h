#pragma once
#include <memory>

namespace boop {
	class GameObject;
}

namespace booble
{
	class Player final
	{
	public:
		static std::unique_ptr<boop::GameObject> CreatePlayer();
	};

}