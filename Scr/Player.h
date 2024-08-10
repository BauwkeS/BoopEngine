#pragma once
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/SpriteComponent.h"
#include "../BoopEngine/Boop/States.h"
#include "../BoopEngine/Boop/GameObject.h"

//player needs the states
//the input ?
//lives
//score?
//movement

namespace booble
{
	class Player final
	{
	public:
		static std::unique_ptr<boop::GameObject> CreatePlayer();
	};

}