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
		virtual void StopMusic() = 0;
		virtual void StopSound()=0;
		virtual void StopAll() = 0;
		virtual void SetMuting(bool muting)=0;
		virtual bool IsMuted() const { return false; }
	};


	class SoundSystemNull final : public SoundSystem
	{
	public:
		void PlaySound(const std::string&, const float) override {};
		void PlayMusic(const std::string&, const float) override {};
		void StopMusic() override {};
		void StopSound() override {};
		void StopAll() override {};
		void SetMuting(bool) override {};
		bool IsMuted() const override { return false; }
	};


	class SDL2SoundSystem final : public SoundSystem
	{
	private:
		class SDL2SoundSystemImpl;
		std::unique_ptr<SDL2SoundSystemImpl> m_SoundSysImpl{};
	public:
		SDL2SoundSystem();
		~SDL2SoundSystem();
		void PlaySound(const std::string& file, const float volume) override;
		void PlayMusic(const std::string& file, const float volume) override;
		void StopMusic() override;
		void StopSound() override;
		void StopAll() override;
		void SetMuting(bool muting) override;
		bool IsMuted() const override;
	};
}