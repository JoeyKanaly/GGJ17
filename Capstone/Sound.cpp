#ifndef SOUND_H
#include "Sound.h"
#endif

Sound::Sound(std::string path, FMOD::System* system) :
	shouldRepeat(false)
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

void Sound::stopSound(FMOD::System* system)
{
	channel->setPaused(true);
	channel->setPosition(0, FMOD_TIMEUNIT_MS);
}

void Sound::setGroup(FMOD::ChannelGroup * group)
{
	this->group = group;
}

void Sound::setShouldRepeat(bool value)
{
	shouldRepeat = value;
}
