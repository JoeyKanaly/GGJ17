#ifndef SOUNDMANAGER_H
#include "SoundManager.h"
#endif

SoundManager::SoundManager()
{
	initFMOD();
}

void SoundManager::addSound(std::string soundName, std::string path, soundType typeOfSound)
{
	sounds.insert(std::make_pair(soundName, Sound(path, system)));
	
	switch (typeOfSound)
	{
	case soundType::BACKGROUND:
		sounds[soundName].setGroup(music);
		sounds[soundName].setShouldRepeat(true);
		break;
	case soundType::SOUNDEFFECT:
		sounds[soundName].setGroup(soundEffects);
		break;
	}
}

void SoundManager::playSound(std::string soundName)
{
	sounds[soundName].playSound(system);
}

void SoundManager::reduceVolume(soundType sT)
{
	float currentVolume;
	switch (sT)
	{
	case soundType::BACKGROUND:
		music->getVolume(&currentVolume);
		music->setVolume(std::max(currentVolume - 0.05f, 0.0f));
		break;
	case soundType::SOUNDEFFECT:
		soundEffects->getVolume(&currentVolume);
		soundEffects->setVolume(std::max(currentVolume - 0.1f, 0.0f));
		break;
	}
}

void SoundManager::setVolume(soundType sT, float vol)
{
	switch (sT)
	{
	case soundType::BACKGROUND:
		music->setVolume(vol);
		break;
	case soundType::SOUNDEFFECT:
		soundEffects->setVolume(vol);
		break;
	}
}

void SoundManager::stopSound(std::string soundName)
{
	sounds[soundName].stopSound(system);
}

void SoundManager::increaseVolume(soundType sT)
{
	float currentVolume;
	switch (sT)
	{
	case soundType::BACKGROUND:
		music->getVolume(&currentVolume);
		music->setVolume(std::max(currentVolume + 0.1f, 0.0f));
		break;
	case soundType::SOUNDEFFECT:
		soundEffects->getVolume(&currentVolume);
		soundEffects->setVolume(std::max(currentVolume + 0.1f, 0.0f));
		break;
	}
}

void SoundManager::update()
{
	system->update();
}

void SoundManager::initFMOD()
{
	handleFMODError(FMOD::System_Create(&system));
	handleFMODError(system->init(SOUND_MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr));
	createChannelGroups();
}

void SoundManager::createChannelGroups()
{
	handleFMODError(system->createChannelGroup(NULL, &music));
	handleFMODError(system->createChannelGroup(NULL, &soundEffects));
}