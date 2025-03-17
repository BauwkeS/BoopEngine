#pragma once
#include "Event.h"

namespace boop
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer(){}
		virtual void OnNotify(Event event)=0;
	};

}
