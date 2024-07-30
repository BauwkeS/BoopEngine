#pragma once

namespace boop
{
	class GameObject;

	enum struct Event
	{
		LevelStart,
		PlayerDied,
		EnemyDied
	};

	class Observer
	{
	public:
		virtual ~Observer(){}
		virtual void OnNotify(GameObject& gameObject, Event& event);
	};

}
