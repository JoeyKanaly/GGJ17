#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#define SOUND_MAX_CHANNELS 32

#include <map>
#include <algorithm>
#include "Sound.h"

enum class soundType
{
	BACKGROUND,
	SOUNDEFFECT
};

class SoundManager
{
public:
	SoundManager();
	void addSound(std::string soundName, std::string path, soundType typeOfSound);
	void playSound(std::string soundName);
	void reduceVolume(soundType sT);
	void increaseVolume(soundType sT);
	void setVolume(soundType sT, float vol);
	void stopSound(std::string soundName);
	void update();
private:
	FMOD::System* system;
	FMOD::ChannelGroup *music, *soundEffects;
	std::map<std::string, Sound> sounds;
	void initFMOD();
	void createChannelGroups();
};

#endif