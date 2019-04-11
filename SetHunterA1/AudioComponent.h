/*
	https://bell0bytes.eu/the-basics-of-xaudio2/
*/

#pragma once
#include "AudioEngine.h"
#include "SoundEvent.h"


class AudioComponent
{
private:
	AudioEngine* engine;	// the main audio engine

public:
	AudioComponent();
	~AudioComponent();

	// Load files from disk
	bool LoadFile(const std::wstring fileName, SoundEvent& soundEvent);

	// play sound
	bool PlaySoundEvent(const SoundEvent& soundEvent);
	bool StopSoundEvent(const SoundEvent& soundEvent);
};

