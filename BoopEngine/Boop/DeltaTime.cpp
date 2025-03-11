#include "DeltaTime.h"

void boop::DeltaTime::SetDeltaTime(const float updatedDeltaTime)
{
	m_DeltaTime = updatedDeltaTime;
}

float boop::DeltaTime::GetDeltaTime() const
{
	return m_DeltaTime;
}
