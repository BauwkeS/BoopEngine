#include "SoundSystem.h"
#include <memory>
#include "ServiceLocator.h"
#include <iostream>

std::unique_ptr<boop::SoundSystem> boop::ServiceLocator::m_SoundSystemInstance{ std::make_unique<SoundSystemNull>() };

void boop::SoundSystemNull::PlaySound(const unsigned short, const float)
{
	// code that actually plays sound here
}

void boop::SoundSystemLogger::PlaySound(const unsigned short id, const float volume)
{
	//Log the sound play action
		std::cout << "Playing sound with ID: " << id << " at volume: " << volume << std::endl;
}
