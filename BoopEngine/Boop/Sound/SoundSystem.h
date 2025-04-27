#pragma once

namespace boop
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void PlaySound(const unsigned short id, const float volume) = 0;
	};


	class SoundSystemNull final : public SoundSystem
	{
	public:
		void PlaySound(const unsigned short id, const float volume) override;
	};


	class SoundSystemLogger final : public SoundSystem
	{
	public:
		void PlaySound(const unsigned short id, const float volume) override;
	};
}