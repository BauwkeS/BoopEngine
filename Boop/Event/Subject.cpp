#include "Subject.h"

boop::Subject::~Subject()
{
	for (auto observer : m_Observers)
	{
		delete observer;
		observer = nullptr;
	}
}

void boop::Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void boop::Subject::RemoveObserver(Observer* observer)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(),observer);
	m_Observers.erase(it);

	//reference:
	//https://www.geeksforgeeks.org/how-to-remove-an-element-from-vector-in-cpp/
}

void boop::Subject::Notify(GameObject& gameObject, Event event)
{
	for (auto observer : m_Observers)
	{
		observer->OnNotify(gameObject, event);
	}
}
