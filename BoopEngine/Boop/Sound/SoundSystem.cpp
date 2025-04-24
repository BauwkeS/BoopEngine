#include "SoundSystem.h"
#include <memory>
#include "ServiceLocator.h"
#include <iostream>

void boop::SoundSystemNull::Play(const unsigned short id, const float volume)
{
	// code that actually plays sound here
}

std::unique_ptr<boop::SoundSystem> boop::ServiceLocator::m_SoundSystemInstance{ std::make_unique<SoundSystemNull>() };

void boop::SoundSystemLogger::Play(const unsigned short id, const float volume)
{
	//Log the sound play action
		std::cout << "Playing sound with ID: " << id << " at volume: " << volume << std::endl;
}
