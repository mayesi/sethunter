/*
	https://bell0bytes.eu/the-basics-of-xaudio2/
*/

#pragma once
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#include <vector>
#include <string>

// Windows Media Foundation
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

//forward declaration
class AudioComponent;

class AudioEngine
{
private:
	IXAudio2* dev;
	IXAudio2MasteringVoice* masterVoice;
	IMFAttributes* sourceReaderConfiguration; // Windows Media Foundation Source Reader Configuration

public:
	AudioEngine();
	~AudioEngine();

	bool Init();
	bool LoadFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** waveFormatEx, unsigned int& waveFormatLength);

	friend class AudioComponent;
};

