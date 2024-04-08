#pragma once
#include "Singleton.h"

namespace boop
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
