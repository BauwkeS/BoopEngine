#include "Subject.h"

void boop::Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void boop::Subject::RemoveObserver(Observer* observer)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(),observer);
	m_Observers.erase(it);
}

void boop::Subject::NotifyObserver(Event event)
{
	for (auto observer : m_Observers)
	{
		observer->OnNotify(event);
	}
}
