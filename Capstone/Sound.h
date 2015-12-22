#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <fmod\fmod.hpp>
#include "Tools.h"

class Sound
{
public:
	Sound() {};
	Sound(std::string path, FMOD::System* system);
	void playSound(FMOD::System* system);
	void stopSound(FMOD::System * system);
	void setGroup(FMOD::ChannelGroup* group);
	void setShouldRepeat(bool value);
private:
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	FMOD::ChannelGroup* group;
	bool shouldRepeat;
};

#endif