#include "SoundSystem.h"
#include <memory>
#include "ServiceLocator.h"
#include <iostream>
#include <SDL_mixer.h>
#include <SDL.h>
#include <vector>

std::unique_ptr<boop::SoundSystem> boop::ServiceLocator::m_SoundSystemInstance{ std::make_unique<SoundSystemNull>() };

class boop::SDL2SoundSystem::SDL2SoundSystemImpl final
{
private:
	std::vector<Mix_Chunk*> m_SoundEffects{ };
	Mix_Music* m_Music{ nullptr };

public:
	SDL2SoundSystemImpl() {
		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	}
	~SDL2SoundSystemImpl() {
		for (auto& sound : m_SoundEffects) {
			Mix_FreeChunk(sound);
		}
		if (m_Music) {
			Mix_FreeMusic(m_Music);
		}
		Mix_CloseAudio();
		SDL_Quit();
	}
	void PlaySound(const std::string& file, const float volume)
	{
		std::string fullFile = ("Data\\sounds\\" + file); // Ensure the file path is correct


		// Implementation for playing sound using SDL2
		Mix_Chunk* sound = Mix_LoadWAV(fullFile.c_str());
		if (!sound) {
			std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
			return;
		}
		Mix_VolumeChunk(sound, static_cast<int>(volume * MIX_MAX_VOLUME));
		if (Mix_PlayChannel(-1, sound, 0) == -1) {
			std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
		}
		else {
			m_SoundEffects.push_back(sound);
		}
	}

	void PlayMusic(const std::string& file, const float volume)
	{
		std::string fullFile = ("Data\\sounds\\" + file); // Ensure the file path is correct

		// Implementation for playing music using SDL2
		if (m_Music) {
			Mix_FreeMusic(m_Music);
		}
		m_Music = Mix_LoadMUS(fullFile.c_str());
		if (!m_Music) {
			std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
			return;
		}
		Mix_VolumeMusic(static_cast<int>(volume * MIX_MAX_VOLUME));
		if (Mix_PlayMusic(m_Music, -1) == -1) {
			std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
		}
	}
	void StopMusic()
	{
		if (m_Music) {
			Mix_HaltMusic();
			Mix_FreeMusic(m_Music);
			m_Music = nullptr;
		}
	}

	void StopSound()
	{
		for (auto& sound : m_SoundEffects) {
			Mix_HaltChannel(-1); // Stop all channels
			Mix_FreeChunk(sound);
		}
		m_SoundEffects.clear();
	}

};

boop::SDL2SoundSystem::SDL2SoundSystem()
	: m_SoundSysImpl(std::make_unique<SDL2SoundSystemImpl>())
{
}

boop::SDL2SoundSystem::~SDL2SoundSystem()
{
}

void boop::SDL2SoundSystem::PlaySound(const std::string& file, const float volume)
{
	m_SoundSysImpl->PlaySound(file, volume);
}

void boop::SDL2SoundSystem::PlayMusic(const std::string& file, const float volume)
{
	m_SoundSysImpl->PlayMusic(file, volume);
}

void boop::SDL2SoundSystem::StopMusic()
{
	m_SoundSysImpl->StopMusic();
}
void boop::SDL2SoundSystem::StopSound()
{
	m_SoundSysImpl->StopSound();
}

void boop::SDL2SoundSystem::StopAll()
{
	m_SoundSysImpl->StopMusic();
	m_SoundSysImpl->StopSound();
}
