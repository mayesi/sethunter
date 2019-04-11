#include "AudioComponent.h"


AudioComponent::AudioComponent()
{	
	engine = new AudioEngine();	// Create an audio engine
	engine->Init();
}


AudioComponent::~AudioComponent()
{
}

// Calls the LoadFile method from the audio engine class
bool AudioComponent::LoadFile(const std::wstring fileName, SoundEvent & soundEvent)
{
	HRESULT hr;
	bool result;

	// load file into wave
	WAVEFORMATEX* waveFormatEx;
	result = engine->LoadFile(fileName, soundEvent.audioData, &waveFormatEx, soundEvent.waveLength);
	if (!result)
		return result;
	soundEvent.waveFormat = *waveFormatEx;

	// create source voice
	hr = engine->dev->CreateSourceVoice(&soundEvent.sourceVoice, &soundEvent.waveFormat);
	if (FAILED(hr))
		return false;

	// Fill the XAUDIO2 buffer
	ZeroMemory(&soundEvent.audioBuffer, sizeof(XAUDIO2_BUFFER));
	soundEvent.audioBuffer.AudioBytes = (UINT32)soundEvent.audioData.size();
	soundEvent.audioBuffer.pAudioData = (BYTE* const)&soundEvent.audioData[0];
	soundEvent.audioBuffer.pContext = nullptr;

	return true;
}


bool AudioComponent::PlaySoundEvent(const SoundEvent& soundEvent)
{
	// handle errors
	HRESULT hr;

	// submit the audio buffer to the source voice
	hr = soundEvent.sourceVoice->SubmitSourceBuffer(&soundEvent.audioBuffer);
	if (FAILED(hr))
		return false;

	// start the source voice
	soundEvent.sourceVoice->Start();

	// return success
	return true;
}

bool AudioComponent::StopSoundEvent(const SoundEvent& soundEvent)
{
	soundEvent.sourceVoice->Stop();

	return true;
}
