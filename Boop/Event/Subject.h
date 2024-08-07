#pragma once
#include <vector>
#include <Event/Observer.h>

namespace boop
{
	class GameObject;

	class Subject
	{
	private:
		std::vector<Observer*> m_Observers{};

	public:
		Subject()=default;
		~Subject();

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		void Notify(GameObject& gameObject, Event event);
	};
}
