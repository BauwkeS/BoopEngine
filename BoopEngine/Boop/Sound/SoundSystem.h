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
	private:
		SoundSystem& m_SoundSystemWrapped;
	public:
		SoundSystemLogger(SoundSystem& soundSystemWrapped)
			: m_SoundSystemWrapped(soundSystemWrapped) {
		}
		virtual void PlaySound(const unsigned short id, const float volume) override;
	};
}