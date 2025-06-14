#pragma once
#include <memory>
#include <string>

namespace boop
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void PlaySound(const std::string& file, const float volume) = 0;
		virtual void PlayMusic(const std::string& file, const float volume) = 0;
	};


	class SoundSystemNull final : public SoundSystem
	{
	public:
		void PlaySound(const std::string&, const float) override {};
		void PlayMusic(const std::string&, const float) override {};
	};


	class SDL2SoundSystem final : public SoundSystem
	{
	private:
		class SDL2SoundSystemImpl;
		std::unique_ptr<SDL2SoundSystemImpl> m_SoundSysImpl{};
	public:
	/*	SDL2SoundSystem(SoundSystem& ssImpl)
			: m_SoundSysImpl(ssImpl) {
		}*/
		SDL2SoundSystem();
		~SDL2SoundSystem();
		void PlaySound(const std::string& file, const float volume) override;
		void PlayMusic(const std::string& file, const float volume) override;
	};
}