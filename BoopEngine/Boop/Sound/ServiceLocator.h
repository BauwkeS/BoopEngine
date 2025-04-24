#pragma once
#include <memory>
#include "SoundSystem.h"

namespace boop
{
	class ServiceLocator final
	{
		static std::unique_ptr<boop::SoundSystem> m_SoundSystemInstance;
	public:
		static void RegisterSoundSystem(std::unique_ptr<boop::SoundSystem>&& soundSystem)
		{
			m_SoundSystemInstance = soundSystem == nullptr ? std::make_unique<SoundSystemNull>() : std::move(soundSystem);
		}
		static boop::SoundSystem* GetSoundSystem()
		{
			return m_SoundSystemInstance.get();
		}
	};
}


