#pragma once

#include "HelperFiles/Singleton.h"

//better to not use an event queue because it can make things more complicated than an observer,
// definitely for a smaller project/ Maybe handy for a sound system? Depending on what you will
// do later, but definitely need some extra research on this topic if you want

namespace boop
{
	class Event final : public Singleton<Event>
	{

	private:
		enum EventType {
			LevelStart,
			PlayerDied,
			EnemyDied
		};

		
	public:

	};
}