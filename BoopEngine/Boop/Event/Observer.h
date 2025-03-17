#pragma once

namespace boop
{
	class GameObject;

    class Event
    {
    public:
        virtual ~Event() = default;
    };

	class Observer
	{
	public:
		virtual ~Observer(){}
		virtual void OnNotify(Event& event)=0;
	};

}
