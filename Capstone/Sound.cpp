#ifndef SOUND_H
#include "Sound.h"
#endif

Sound::Sound(std::string path, FMOD::System* system)
{
	handleFMODError(system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &sound));
}

void Sound::playSound(FMOD::System* system)
{
	system->playSound(sound, group, false, &channel);
	if (shouldRepeat)
	{
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);
	}
}

void Sound::setGroup(FMOD::ChannelGroup * group)
{
	this->group = group;
}

void Sound::setShouldRepeat(bool value)
{
	shouldRepeat = value;
}
