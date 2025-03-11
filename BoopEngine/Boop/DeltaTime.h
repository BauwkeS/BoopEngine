#pragma once
#include "HelperFiles/Singleton.h"

namespace boop
{
	class DeltaTime final : public Singleton<DeltaTime>
	{
	public:
		void SetDeltaTime(const float updatedDeltaTime);
		float GetDeltaTime() const;
	private:
		float m_DeltaTime{};
	};
}
