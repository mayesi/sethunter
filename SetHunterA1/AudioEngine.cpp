/*
	Music by Eric Matyas
	www.soundimage.org
*/

#include "AudioEngine.h"

// Constructor for the AudioEngine class
AudioEngine::AudioEngine()
{
	dev = NULL;
	masterVoice = NULL;
	sourceReaderConfiguration = NULL;
}

// Destructor
AudioEngine::~AudioEngine()
{
	// shut down windows media foundation
	MFShutdown();

	// destroy the master voice
	masterVoice->DestroyVoice();

	// stop the engine
	dev->StopEngine();
}

/*
	Method:		Init()
	Description:
		Initializes the XAudio2 engine.
*/
bool AudioEngine::Init()
{
	HRESULT hr;

	// Initialize windows media foundation
	if (FAILED(hr = MFStartup(MF_VERSION)))
		return false;

	// Initialize the source reader, create an IMFAttributes interface
	if (FAILED(hr = MFCreateAttributes(&sourceReaderConfiguration, 1)))
		return false;
	
	// Tell the source reader we want no latency
	if (FAILED(hr = sourceReaderConfiguration->SetUINT32(MF_LOW_LATENCY, true)))
		return false;

	// Create an instance of the XAudio engine
	if (FAILED(hr = XAudio2Create(&dev, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return false;

	// Create the mastering voice
	if (FAILED(hr = dev->CreateMasteringVoice(&masterVoice)))
		return false;

	return true;
}

bool AudioEngine::LoadFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** waveFormatEx, unsigned int& waveFormatLength)
{
	HRESULT hr;
	
	// stream index
	DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;
	
	// Create the source reader
	IMFSourceReader* sourceReader;
	if (FAILED (hr = MFCreateSourceReaderFromURL(
		filename.c_str(), 
		sourceReaderConfiguration, 
		&sourceReader)))
		return false;

	// select the first audio stream, and deselect all other streams
	if (FAILED(hr = sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false)))
		return false;

	if (FAILED(hr = sourceReader->SetStreamSelection(streamIndex, true)))
		return false;
		
	// query information about the media file
	IMFMediaType* nativeMediaType;
	if (FAILED(hr = sourceReader->GetNativeMediaType(streamIndex, 0, &nativeMediaType)))
		return false;

	// make sure that this is really an audio file
	GUID majorType{};
	hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
	if (majorType != MFMediaType_Audio)
		return false;

	// check whether the audio file is compressed or uncompressed
	GUID subType{};
	hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType);
	if (!(subType == MFAudioFormat_Float || subType == MFAudioFormat_PCM))
	{
		// the audio file is compressed; we have to decompress it first
		// to do so, we inform the SourceReader that we want uncompressed data
		// this causes the SourceReader to look for decoders to perform our request
		IMFMediaType* partialType = nullptr;
		if (FAILED(hr = MFCreateMediaType(&partialType)))
			return false;

		// set the media type to "audio"
		if (FAILED(hr = partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio)))
			return false;

		// request uncompressed data
		if (FAILED(hr = partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM)))
			return false;

		if (FAILED(hr = sourceReader->SetCurrentMediaType(streamIndex, NULL, partialType)))
			return false;
	}

	// uncompress the data and load it into an XAudio2 Buffer
	IMFMediaType* uncompressedAudioType = nullptr;
	if (FAILED(hr = sourceReader->GetCurrentMediaType(streamIndex, &uncompressedAudioType)))
		return false;

	if (FAILED(hr = MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType, waveFormatEx, &waveFormatLength)))
		return false;

	// ensure the stream is selected
	if (FAILED(hr = sourceReader->SetStreamSelection(streamIndex, true)))
		return false;

	// copy data into byte vector
	IMFSample* sample = nullptr;
	IMFMediaBuffer* buffer = nullptr;
	BYTE* localAudioData = NULL;
	DWORD localAudioDataLength = 0;

	while (true)
	{
		DWORD flags = 0;
		
		if (FAILED(hr = sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, &sample)))
			return false;

		// check whether the data is still valid
		if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
			break;

		// check for eof
		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
			break;

		if (sample == nullptr)
			continue;

		// convert data to contiguous buffer
		if (FAILED(hr = sample->ConvertToContiguousBuffer(&buffer)))
			return false;

		// lock buffer and copy data to local memory
		if (FAILED(hr = buffer->Lock(&localAudioData, nullptr, &localAudioDataLength)))
			return false;

		for (size_t i = 0; i < localAudioDataLength; i++)
			audioData.push_back(localAudioData[i]);

		// unlock the buffer
		hr = buffer->Unlock();
		localAudioData = nullptr;

		if (FAILED(hr))
			return false;
	}

	return true;
}
